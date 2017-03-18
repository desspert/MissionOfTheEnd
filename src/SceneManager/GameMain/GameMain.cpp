#include "GameMain.h"
#include "cinder/ObjLoader.h"
#include "../../Utility/SoundManager.h"
#include "../../Objects/MaterialObjects/Cube/Cube.h"
#include "../../Objects/MaterialObjects/Sphere/Sphere.h"
#include "../../Objects/Camera/Camera.h"
#include "../../Objects/MaterialObjects/DamageObjects/Player/Player.h"
#include "../../Objects/MaterialObjects/Map/Map.h"
#include "../../Objects/MaterialObjects/Weapon/Tompson/Tompson.h"
#include "../../Objects/MaterialObjects/Weapon/AK/AK.h"
#include "../../Objects/MaterialObjects/Weapon/Deagle/Deagle.h"
#include "../../Objects/MaterialObjects/Weapon/PK/PK.h"
#include "../../Objects/MaterialObjects/DamageObjects/Enemys/NormalEnemy/NormalEnemy.h"
#include "../../Objects/Spawner/Spawner.h"
#include "../../Utility/Collision.h"
GameMain::GameMain()
{
}
void rayToMeshCollision(ci::Ray ray, ci::Vec3f& result,
	const std::vector<ci::Vec3f>& vertices,
	const std::vector<uint32_t>& indices) {
	for (unsigned int i = 0; i < indices.size(); i += 3) {
		uint32_t v0 = indices[i];
		uint32_t v1 = indices[i + 1];
		uint32_t v2 = indices[i + 2];

		float z;
		if (ray.calcTriangleIntersection(vertices[v0], vertices[v1], vertices[v2], &z)) {
			// 5. 交差判定で得られたZ座標から、XYZを求める
			//    Ray::calcPosition が使える
			result = ray.calcPosition(z);
			break;
		}
	}
}

void GameMain::rayToAABBCollision(std::shared_ptr<ObjectBase>& obj, ci::Ray ray, ci::Vec3f& result) {
	std::vector<float> buf;

	float t[3] = { 0.0f };
	if (obj->getAABB()->intersect(ray, t)) {
		if (t[0] > 0 && t[0] <= 1) {
			buf.push_back(t[0]);
		}
		if (t[1] > 0 && t[1] <= 1) {
			buf.push_back(t[1]);
		}
	}


	if (!buf.empty())
	{
		auto itr = std::min_element(buf.begin(), buf.end());
		ci::Vec3f buf1 = player->getPos() - result;
		ci::Vec3f buf2 = player->getPos() - ray.calcPosition(*itr);
		if (buf1.length() > buf2.length()) {
			result = ray.calcPosition(*itr);
			return;
		}
	}
	else {
		result = ci::Vec3f(1000.0f, 1000.0f, 1000.0f);
	}
}

void GameMain::enemysPathAdd()
{
	enemys_path.push_back(EnemyPath(
		"Objects/Enemys/Normal/chr_2.obj",
		"Objects/Enemys/Normal/chr_2a.obj",
		"Objects/Enemys/Normal/chr_2.png",
		"Objects/Enemys/Normal/chr_2a.png"));

	enemys_path.push_back(EnemyPath(
		"Objects/Enemys/Jump/chr_3.obj",
		"Objects/Enemys/Jump/chr_3a.obj",
		"Objects/Enemys/Jump/chr_3.png",
		"Objects/Enemys/Jump/chr_3a.png"));

	enemys_path.push_back(EnemyPath(
		"Objects/Enemys/Fast/chr_knight.obj",
		"Objects/Enemys/Fast/chr_knighta.obj",
		"Objects/Enemys/Fast/chr_knight.png",
		"Objects/Enemys/Fast/chr_knighta.png"));
}

//エネミーは大量に出現するので
//あらかじめ読み込んだデータをコピーして
//使いまわすことにより処理を軽減させる
void GameMain::enemysLoading()
{
	enemysPathAdd();
	for (int i = 0; i < enemys_path.size(); i++) {
		ci::TriMesh body;
		ci::TriMesh left_leg;
		ci::TriMesh right_leg;

		ci::ObjLoader loader_body = ci::ObjLoader(ci::app::loadAsset(enemys_path[i].body_path));
		ci::ObjLoader loader_leg = ci::ObjLoader(ci::app::loadAsset(enemys_path[i].leg_path));

		loader_body.load(&body, boost::logic::indeterminate, boost::logic::indeterminate,
			false);
		loader_leg.load(&left_leg, boost::logic::indeterminate, boost::logic::indeterminate,
			false);
		loader_leg.load(&right_leg, boost::logic::indeterminate, boost::logic::indeterminate,
			false);

		enemys_mesh.push_back(EnemyData(body, left_leg, right_leg));
	}
}

void GameMain::mapObjectsSetup()
{
	enemysLoading();
	res = std::make_shared<Sphere>(ci::Vec3f(0, 0, 0), ci::Vec3f(0.1f, 0.1f, 0.1f), ci::Vec3f(0, 0, 0), "jimen", "Objects/Wall/039.jpg");
	skydome = std::make_shared<Sphere>(ci::Vec3f(0, 0, 0), ci::Vec3f(1000, 1000, 1000), ci::Vec3f(0, 0, 0), "skydome", "Objects/SkyDome/Skydome151004y.jpg");
	player = std::make_shared<Player>(ci::Vec3f(0, 10, 4), ci::Vec3f(1, 6, 1), ci::Vec3f(0, 0, 0), "", "");

	object.push_back(std::make_shared<Cube>(ci::Vec3f(0, 1, 4), ci::Vec3f(1, 1, 1), ci::Vec3f(0, 0, 0), "jimen", "Objects/Wall/039.jpg"));


	map = std::make_shared<Map>(ci::Vec3f(0, -3, 4), ci::Vec3f(100, 10, 100), ci::Vec3f(0, 0, 0), "map", "Objects/Map/20141130172655.jpg", "Objects/Map/terrain.obj");
	map->setup();
	//weapons.push_back(std::make_shared<Tompson>(ci::Vec3f(0, 10, 4), ci::Vec3f(0.01f, 0.01f, 0.01f), ci::Vec3f(0, 0, 0), "Tompson", "Objects/Weapons/Tompson/Game_Camio_Vent_TommyGun_DIFF.png"));
	weapons.push_back(std::make_shared<AK>(ci::Vec3f(0, 10, 4), ci::Vec3f(0.004f, 0.004f, 0.004f), ci::Vec3f(0, 0, 0), "AK", "Objects/Weapons/AK/cfn_01_b.jpg"));
	//weapons.push_back(std::make_shared<Deagle>(ci::Vec3f(0, 10, 4), ci::Vec3f(0.01f, 0.01f, 0.01f), ci::Vec3f(0, 0, 0), "Deagle", "Objects/Weapons/Deagle/pist_deagle.jpg"));
	//weapons.push_back(std::make_shared<PK>(ci::Vec3f(0, 10, 4), ci::Vec3f(0.004f, 0.004f, 0.004f), ci::Vec3f(0, 0, 0), "PK", "Objects/Weapons/PK/WP2d00_BM_01.png"));
	player->setup();
	skydome->setup();
	res->setup();

	spawner.push_back(std::make_shared<Spawner>(ci::Vec3f(0, 10, 10), ci::Vec3f(3, 0, 3), ci::Vec3f(0, 0, 0), 100, 30, 0.08f));

	for (auto& it : object) {
		it->setup();
	}
	for (auto& it : weapons) {
		it->setup();
	}
}

void GameMain::mapTipSetup()
{
	//std::ifstream ifs;
	//ifs.open("../assets/test.txt");
	//int wepn = 0;
	//for (int z = 0; z < 150; z++) {
	//	for (int x = 0; x < 174; x++) {
	//		int f;
	//		ifs >> f;
	//		switch (f)
	//		{
	//		case 0:
	//			break;
	//		case 1:
	//			//object.push_back(std::make_shared<CubeMaterial>(Vec3f(x, 0.5f, z), Vec3f(1, 1, 1), Vec3f(0, 0, 0), Vec3f(0, 0, 0), "bill", "img_9.jpg"));
	//			object.push_back(std::make_shared<Goal>(Vec3f(x, 0.5f, z), Vec3f(1, 1, 1), Vec3f(0, 0, 0), Vec3f(0, 0, 0)));
	//			break;
	//		case 2:
	//			object.push_back(std::make_shared<CubeMaterial>(Vec3f(x, 1, z), Vec3f(1, 2, 1), Vec3f(0, 0, 0), Vec3f(0, 0, 0), "bill", "img_9.jpg"));
	//			break;
	//		case 3:
	//			object.push_back(std::make_shared<CubeMaterial>(Vec3f(x, 1.5, z), Vec3f(1, 3, 1), Vec3f(0, 0, 0), Vec3f(0, 0, 0), "bill", "img_9.jpg"));
	//			break;
	//		case 4:
	//			CAMERA.setPos(Vec3f(x, 1, z));
	//			break;
	//		case 5:
	//			object.push_back(std::make_shared<CubeMaterial>(Vec3f(x, 2.5f, z), Vec3f(1, 5, 1), Vec3f(0, 0, 0), Vec3f(0, 0, 0), "bill", "img_9.jpg"));
	//			break;
	//		case 6:
	//			spawn.push_back(std::make_shared<Spawner>(Vec3f(x, 1, z), Vec3f(3, 0, 3), 100, 30, 0.08f));
	//			break;
	//		case 7:
	//			wepn++;
	//			if (wepn == 1) {
	//				weapons.push_back(std::make_shared<MG>(Vec3f(x, 1, z), Vec3f(2, 2, 2), Vec3f(0, 0, 0), Vec3f(0, 0, 0)));
	//			}
	//			if (wepn == 2) {
	//				weapons.push_back(std::make_shared<AK>(Vec3f(x, 1, z), Vec3f(2, 2, 2), Vec3f(0, 0, 0), Vec3f(0, 0, 0)));
	//			}
	//			if (wepn == 3) {
	//				weapons.push_back(std::make_shared<Tompson>(Vec3f(x, 1, z), Vec3f(2, 2, 2), Vec3f(0, 0, 0), Vec3f(0, 0, 0)));
	//			}
	//			break;
	//		}
	//	}
	//}
	//
	//ifs.close();
}
void GameMain::lightSetup()
{
	light = std::make_shared<ci::gl::Light>(ci::gl::Light::DIRECTIONAL, 0);
	light->setPosition(ci::Vec3f(0, 30, 0));
	light->setAmbient(ci::Color(1.0f, 1.0f, 1.0f));
	light->setDiffuse(ci::Color(0, 0, 0));
	light->setSpecular(ci::Color(0, 0, 0));
	light->setDirection(ci::Vec3f(0.0f, -1.0f, 0.0f));
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
}
void GameMain::setup()
{
	/*SE.registerBufferPlayerNode("get", "ak47_clipin.WAV");
	SE.registerFilePlayerNode("bgm", "Voodoo People (Pendulum Mix).m4a");*/

	lightSetup();
	mapObjectsSetup();
	CAMERA.setup();
}

//地面に沿って動くための判定
ci::Vec3f GameMain::rideMap(ci::Ray ray, const ci::Vec3f& pos, const ci::Vec3f& size)
{
	ci::Vec3f ride_map;
	//地面に沿って動くための判定
	rayToMeshCollision(ray, ride_map, map->getVertices(), map->getIndices());

	//地面よりもyが低ければ戻す
	if (ride_map.y > pos.y - (size.y/2)) {
		return ci::Vec3f(pos.x, ride_map.y + (size.y / 2), pos.z);
	}
	return pos;
}


//一番重い
void GameMain::physicsJudge(std::shared_ptr<ObjectBase>& it)
{

	it->setPos(rideMap(it->getRideMapRay(), it->getPos(), it->getSize()));

	//プレイヤーとの物理判定（AABB）
	player->setPos(returnBoxToBox(player->getPos(), player->getSize(), it->getPos(), it->getSize()));

	for (auto& other : object) {
		//オブジェクト同士の物理判定（AABB）
		it->setPos(returnBoxToBox(it->getPos(), it->getSize(), other->getPos(), other->getSize()));
	}

}

void GameMain::collision(std::shared_ptr<ObjectBase>& it)
{

	physicsJudge(it);

	//プレイヤーと接触したらダメージ
	if (collisionBoxToBox(player->getPos(), player->getSize(), it->getPos(), it->getSize())) {
		player->Damage(it->getAttack());
	}
	
	//AABBの当たり判定を持っていたらrayと判定
	if ((it->getAABB()) != nullptr) {
		rayToAABBCollision(it, CAMERA.getRay(), result);
		if (returnBoxToRayPoint(it->getPos(), it->getSize(), result)) {
			for (auto weapon : weapons) {
				if (weapon->isTrigger()) {
					/*for (int i = 0; i < 4; i++) {
						dankon.push_back(std::make_shared<Dankon>(ray_point, Vec3f(0.1, 0.1, 0.1), Vec3f(0, 0, 0), Vec3f(0, 0, 0), object->getWall()));
					}*/
					it->Damage(weapon->getAttack());
					res->setPos(result);
					break;
				}
			}
		}
	}
	//メッシュの判定を持っていたらrayと判定
	if (it->getVertices().size() != 0) {
		rayToMeshCollision(CAMERA.getRay(), result, it->getVertices(), it->getIndices());
	}
}
void GameMain::enemySpawn()
{
	for (auto& it : spawner) {
		it->update();
		if (it->isSpawn()) {
			int type = it->getRandom();
			object.push_back(std::make_shared<NormalEnemy>(
				it->getEnemyPos(), ci::Vec3f(1, 2, 1), ci::Vec3f(0, 0, 0),
				"Enemy" + std::to_string(type), enemys_path[type].body_tex_path,
				"Enemy1_leg" + std::to_string(type), enemys_path[type].leg_tex_path,
				enemys_mesh[type].body,
				enemys_mesh[type].left_leg,
				enemys_mesh[type].right_leg));
		}
	}
}
void GameMain::playerUpdate()
{
	////地面とAimの判定
	//rayToMeshCollision(CAMERA.getRay(), result, map->getVertices(), map->getIndices());
	player->update();
	
	player->setPos(rideMap(player->getRideMapRay(), player->getPos(), player->getSize()));
}
void GameMain::update(const float& delta_time)
{
	playerUpdate();
	enemySpawn();
	for (auto& it : weapons) {
		it->update();
	}
	for (auto& it : object) {
		it->update();
		collision(it);
	}
	isDead();
}

void GameMain::isDead()
{
	for (auto it = object.begin(); it != object.end(); it++) {
		if ((*it)->isDead()) {
			object.erase(it);
			break;
		}
	}
}

void GameMain::draw()
{
	ci::gl::clear(ci::ColorA8u(1, 1, 1, 1));
	ci::gl::enable(GL_LIGHTING);
	ci::gl::enable(GL_NORMALIZE);
	light->enable();
	player->draw();
	for (auto& it : object) {
		it->draw();
	}
	for (auto& it : weapons) {
		it->draw();
	}
	map->draw();
	drawSkyDome();
	res->draw();
	light->disable();

}

void GameMain::drawSkyDome()
{
	glCullFace(GL_FRONT);
	skydome->draw();
	glCullFace(GL_BACK);
}

