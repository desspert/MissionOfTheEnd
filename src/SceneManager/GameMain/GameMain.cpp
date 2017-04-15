#include "GameMain.h"
#include "cinder/ObjLoader.h"
#include "../../Utility/SoundManager.h"
#include "../../Utility/Input/Input.h"
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
#include "../../dessUI/UIPlate/GameMainUI/GameMainUI.h"
#include "../../Objects/MaterialObjects/Perticle/Perticle.h"
#include "../../Objects/MaterialObjects/DamageObjects/BreakWall/BreakWall.h"
#include "../../Objects/MaterialObjects/Goal/Goal.h"
#include "../../Objects/MaterialObjects/DamageObjects/Enemys/Boss/Boss.h"
GameMain::GameMain()
{
	is_goal = false;
	boss_dead = false;
	boss_mode = false;
	goal_count = 0;
	boss_pos = ci::Vec3f(0, 0, 0);
	spawn_count = 0;
	dead_count = 0;
	player_dead_count = 0;
}

float rayToMeshCollision(ci::Ray ray, ci::Vec3f& result,
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
			return z;
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

void GameMain::isGoal()
{
	for (auto& it : goal) {
		if (collisionBoxToBox(player->getPos(), player->getSize(), it->getPos(), it->getSize()))
			is_goal = true;
	}

	if (is_goal) {
		goal_count++;
		if (goal_count == 1) {
			SE.allStop();
			SE.find("victory")->start();
			ui->setGoal();
		}

		if (goal_count == 300) {
			if (!boss_dead) {
				bossSetup();
				boss_mode = true;
			}
			else {
				SE.allStop();
				SE.allCrear();
				SCENE.shift(game::SceneName::RESULT, true);
			}
		}

	}
}

void GameMain::soundSetup()
{
	SE.registerBufferPlayerNode("get", "Sound/SE/Weapons/ak47_clipin.WAV");
	SE.registerFilePlayerNode("bgm", "Sound/Music/bgm_maoudamashii_orchestra21.mp3");
	SE.registerFilePlayerNode("boss_bgm", "Sound/Music/Defeat_Darkness.mp3");
	SE.find("bgm")->start();
	SE.find("bgm")->setLoopEnabled(true);
	SE.find("ready")->start();
}

void GameMain::uiSetup()
{
	ui = std::make_shared<GameMainUI>();
	ui->setup(dess::SceneName::GAMEMAIN);
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
	enemys_path.push_back(EnemyPath(
		"Objects/Enemys/Boss/boss.obj",
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

void GameMain::breakWallSetup()
{
	object.push_back(std::make_shared<BreakWall>(ci::Vec3f(120, 32, 119), ci::Vec3f(5, 14, 19), ci::Vec3f(0, 0, 0), "BreakWall1", "Objects/Wall/114_2566757.jpg", 1000));
	object.push_back(std::make_shared<BreakWall>(ci::Vec3f(77, 44, 130), ci::Vec3f(11, 9, 14), ci::Vec3f(0, 0, 0), "BreakWall2", "Objects/Wall/114_2566757.jpg", 2000));
	object.push_back(std::make_shared<BreakWall>(ci::Vec3f(41, 16, 26), ci::Vec3f(15, 9, 15), ci::Vec3f(0, 0, 0), "BreakWall3", "Objects/Wall/114_2566757.jpg", 3000));
	object.push_back(std::make_shared<BreakWall>(ci::Vec3f(18, 49, 126), ci::Vec3f(16, 10, 21), ci::Vec3f(0, 0, 0), "BreakWall4", "Objects/Wall/114_2566757.jpg", 4000));
}

void GameMain::mapObjectsSetup()
{

	enemysLoading();
	breakWallSetup();
	skydome = std::make_shared<Sphere>(ci::Vec3f(0, 0, 0), ci::Vec3f(1000, 1000, 1000), ci::Vec3f(0, 0, 0), "skydome", "Objects/SkyDome/Skydome151004y.jpg");
	skydome->setup();

	map = new Map(ci::Vec3f(0, -3, 4), ci::Vec3f(100, 10, 100), ci::Vec3f(0, 0, 0), "map", "Objects/Map/20141130172655.jpg", "Objects/Map/terrain.obj");
	map->setup();

	weapons.push_back(std::make_shared<Deagle>(ci::Vec3f(0, 10, 4), ci::Vec3f(0.01f, 0.01f, 0.01f), ci::Vec3f(0, 0, 0), "Deagle", "Objects/Weapons/Deagle/pist_deagle.jpg"));



}

void GameMain::rideOnTerrain()
{
	for (auto& it : goal) {
		it->setup();
		it->update();
		it->setPos(rideMap(it->getRideMapRay(), it->getPos(), it->getSize()));
	}
	for (auto& it : object) {
		it->setup();
		it->update();
		if (it->getObjectType() == ObjectType::BREAKWALL) continue;
		it->setPos(rideMap(it->getRideMapRay(), it->getPos(), it->getSize()));

	}
	for (auto& it : spawner) {
		it->update();
		it->setPos(rideMap(it->getRideMapRay(), it->getPos(), it->getSize()));

	}
	for (auto& it : weapons) {
		it->setup();
		it->setPos(rideMap(it->getRideMapRay(), it->getPos(), it->getSize()));
	}
	player->setup();
	player->update(0);
	player->setPos(rideMap(player->getRideMapRay(), player->getPos(), player->getSize()));
	CAMERA.setPos(player->getPos());
	player->update(0);
}

void GameMain::mapTipSetup(const std::string& map_path)
{
	std::ifstream ifs;
	ifs.open(ci::app::getAssetPath(map_path).string());
	int wepn = 0;
	for (int z = 0; z < 150; z++) {
		for (int x = 0; x < 174; x++) {
			int f;
			ifs >> f;
			switch (f)
			{
			case 0:
				break;
			case 1:
				object.push_back(std::make_shared<Cube>(ci::Vec3f(x, 1, z), ci::Vec3f(1, 1, 1), ci::Vec3f(0, 0, 0), "bill", "Objects/Wall/039.jpg"));
				break;
			case 2:
				object.push_back(std::make_shared<Cube>(ci::Vec3f(x, 1, z), ci::Vec3f(1, 2, 1), ci::Vec3f(0, 0, 0), "bill", "Objects/Wall/039.jpg"));
				break;
			case 3:
				object.push_back(std::make_shared<Cube>(ci::Vec3f(x, 1.5, z), ci::Vec3f(1, 3, 1), ci::Vec3f(0, 0, 0), "bill", "Objects/Wall/039.jpg"));
				break;
			case 4:
				player = std::make_shared<Player>(ci::Vec3f(x, 1, z), ci::Vec3f(1, 3, 1), ci::Vec3f(0, 0, 0), "", "");
				break;
			case 5:
				object.push_back(std::make_shared<Cube>(ci::Vec3f(x, 1, z), ci::Vec3f(1, 6.5f, 1), ci::Vec3f(0, 0, 0), "bill", "Objects/Wall/039.jpg"));
				break;
			case 6:
				spawner.push_back(std::make_shared<Spawner>(ci::Vec3f(x, -10, z), ci::Vec3f(1, 2, 1), ci::Vec3f(0, 0, 0), 100, 30, 0.08f));
				break;
			case 7:
				wepn++;
				if (wepn == 1) {
					weapons.push_back(std::make_shared<PK>(ci::Vec3f(x, 1, z), ci::Vec3f(0.004f, 0.004f, 0.004f), ci::Vec3f(0, 0, 0), "PK", "Objects/Weapons/PK/WP2d00_BM_01.png"));
				}
				if (wepn == 2) {
					weapons.push_back(std::make_shared<AK>(ci::Vec3f(x, 1, z), ci::Vec3f(0.004f, 0.004f, 0.004f), ci::Vec3f(0, 0, 0), "AK", "Objects/Weapons/AK/cfn_01_b.jpg"));
				}
				if (wepn == 3) {
					weapons.push_back(std::make_shared<Tompson>(ci::Vec3f(x, 1, z), ci::Vec3f(0.01f, 0.01f, 0.01f), ci::Vec3f(0, 0, 0), "Tompson", "Objects/Weapons/Tompson/Game_Camio_Vent_TommyGun_DIFF.png"));
				}
				break;
			case 8:
				object.push_back(std::make_shared<Cube>(ci::Vec3f(x, 1, z), ci::Vec3f(6, 12, 6), ci::Vec3f(0, 0, 0), "boss_cube", "Objects/Wall/GameChange.png", true));
				boss_pos = ci::Vec3f(x, 1, z);
				break;
			case 9:
				goal.push_back(std::make_shared<Goal>(ci::Vec3f(x, 0.5f, z), ci::Vec3f(1, 1, 1), ci::Vec3f(0, 0, 0), "", ""));
				break;
			}
		}
	}

	ifs.close();

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

	uiSetup();
	lightSetup();
	mapObjectsSetup();
	mapTipSetup("MapData/Map1.txt");
	rideOnTerrain();
	soundSetup();
}

void GameMain::resetObjects()
{
	goal.clear();
	object.clear();
	spawner.clear();
	weapons.clear();
	delete map;
}

void GameMain::bossSpawn()
{
	if (!boss_mode)return;
	spawn_count++;
	if (spawn_count == 300) {
		ui->bossSetup();
		SE.find("boss_scream")->start();

	}
	if (spawn_count == 360) {
		CAMERA.shakeCamera(1.3f, 0.7f);
		SE.find("boss_landing")->start();
		ui->ui_data["Exprode1"]->setActive(true);
		ui->ui_data["Exprode1"]->setActive(false);
	}
	if (spawn_count == 420) {
		CAMERA.shakeCamera(1.3f, 0.3f);
		SE.find("boss_landing")->start();
		ui->ui_data["Exprode1"]->setActive(true);
		ui->ui_data["Exprode1"]->setActive(false);
	}
	if (spawn_count == 500) {
		for (auto it = object.begin(); it != object.end(); it++) {
			if ((*it)->getObjectType() == ObjectType::BOSSCUBE) {
				object.erase(it);
				break;
			}
		}
		boss.push_back(std::make_shared<Boss>(
			boss_pos, ci::Vec3f(5, 12, 5), ci::Vec3f(0, 0, 0),
			"Enemy3", enemys_path[3].body_tex_path,
			"Enemy1_leg3", enemys_path[3].leg_tex_path,
			enemys_mesh[3].body,
			enemys_mesh[3].left_leg,
			enemys_mesh[3].right_leg));
		for (auto& it : boss) {
			it->setup();
			ui->setBossMaxHP(it->getHp());
		}
		CAMERA.shakeCamera(1.3f, 0.7f);
		SE.find("boss_landing")->start();
		ui->ui_data["Exprode2"]->setActive(true);
		ui->ui_data["Exprode2"]->setActive(false);
	}
}

void GameMain::bossSetup()
{
	SE.registerBufferPlayerNode("boss_walk", "Sound/SE/Boss/small_explosion.mp3");
	SE.registerBufferPlayerNode("boss_landing", "Sound/SE/Boss/landing.mp3");
	SE.registerBufferPlayerNode("boss_dash", "Sound/SE/Boss/short_bomb.mp3");
	SE.registerBufferPlayerNode("boss_effect", "Sound/SE/Boss/sword-clash1.mp3");
	SE.registerBufferPlayerNode("boss_scream", "Sound/SE/Boss/scream.mp3");
	SE.registerBufferPlayerNode("boss_dead", "Sound/SE/Boss/explosion2.mp3");
	ui->ui_data["Message3"]->fontSetText(u8"");
	ui->ui_data["Clear"]->setActive(false);
	resetObjects();
	is_goal = false;
	goal_count = 0;
	map = new Map(ci::Vec3f(0, -3, 4), ci::Vec3f(100, 10, 100), ci::Vec3f(0, 0, 0), "map", "Objects/Map/20141130172655.jpg", "Objects/Map/boss_map.obj");
	map->setup();

	weapons.push_back(std::make_shared<Deagle>(ci::Vec3f(45, 10, 70), ci::Vec3f(0.01f, 0.01f, 0.01f), ci::Vec3f(0, 0, 0), "Deagle", "Objects/Weapons/Deagle/pist_deagle.jpg"));
	mapTipSetup("MapData/boss_map.txt");
	rideOnTerrain();

	SE.find("boss_bgm")->start();
	SE.find("boss_bgm")->setLoopEnabled(true);
}


//地面に沿って動くための判定
ci::Vec3f GameMain::rideMap(ci::Ray ray, const ci::Vec3f& pos, const ci::Vec3f& size)
{
	ci::Vec3f ride_map;
	//地面に沿って動くための判定
	rayToMeshCollision(ray, ride_map, map->getVertices(), map->getIndices());

	//地面よりもyが低ければ戻す
	if (ride_map.y > pos.y - (size.y / 2)) {
		return ci::Vec3f(pos.x, ride_map.y + (size.y / 2), pos.z);
	}
	return pos;
}

//一番重い
void GameMain::physicsJudge(std::shared_ptr<ObjectBase>& it)
{
	//プレイヤーとの物理判定（AABB）
	player->setPos(returnBoxToBox(player->getPos(), player->getSize(), it->getPos(), it->getSize()));


	if (it->getObjectType() != ObjectType::BREAKWALL) {
		it->setPos(rideMap(it->getRideMapRay(), it->getPos(), it->getSize()));
	}
	for (auto& other : object) {

		if (it->getObjectType() == ObjectType::BREAKWALL&&
			other->getObjectType() == ObjectType::WALL) continue;

		//軽減処理
		//近くにある物体以外は返す
		if (!collisionBoxToBox(it->getPos(), ci::Vec3f(3, 3, 3), other->getPos(), other->getSize())) continue;

		//オブジェクト同士の物理判定（AABB）
		it->setPos(returnBoxToBox(it->getPos(), it->getSize(), other->getPos(), other->getSize()));
	}

}

void GameMain::collisionAABB(std::shared_ptr<ObjectBase>& it)
{
	if (!returnBoxToRayPoint(it->getPos(), it->getSize(), result)) return;
	for (auto weapon : weapons) {

		if (!weapon->isTrigger()) continue;
		if (it->getHp() < 0) continue;
		it->Damage(weapon->getAttack());

		if (it->getObjectType() == ObjectType::BREAKWALL) {
			for (int i = 0; i < 4; i++) {
				perticle.push_back(std::make_shared<Perticle>(result, ci::Vec3f(0.1, 0.1, 0.1), ci::Vec3f(0, 0, 0), "", ""));
				perticle.back()->setColor(ci::Vec3f(1, 1, 0));
			}
			break;
		}
		else {
			for (int i = 0; i < 4; i++) {
				perticle.push_back(std::make_shared<Perticle>(result, ci::Vec3f(0.1, 0.1, 0.1), ci::Vec3f(0, 0, 0), "", ""));
			}
			break;
		}
	}


}

void GameMain::collision(std::shared_ptr<ObjectBase>& it)
{

	physicsJudge(it);

	//プレイヤーと接触したらダメージ
	if (collisionBoxToBox(player->getPos(), player->getSize(),
		it->getPos(), it->getSize() + ci::Vec3f(0.1f, 0.1f, 0.1f)) &&
		it->getObjectType() == ObjectType::Enemy) {
		if (it->getHp() > 0) {
			player->Damage(it->getAttack());
		}
	}

	//AABBの当たり判定を持っていたらrayと判定
	if ((it->getAABB()) != nullptr) {
		rayToAABBCollision(it, CAMERA.getRay(), result);
		collisionAABB(it);
	}

}
void GameMain::uiUpdate(const float& delta_time)
{
	ui->update(delta_time);
	ui->setHP(player->getHp());
	for (auto weapon : weapons) {
		if (!weapon->isDrop())
			ui->setBullets(weapon->getBullets());
	}
}
void GameMain::enemySpawn()
{
	for (auto& it : spawner) {
		//プレイヤーから遠ければ処理しない
		if (!collisionBoxToBox(player->getPos(), ci::Vec3f(100, 100, 100), it->getPos(), it->getSize())) continue;

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

//Rayとボスのメッシュのあたり判定
void GameMain::bossCollision()
{
	//Rayの仮置き
	ci::Vec3f orig = CAMERA.getRay().getOrigin();
	ci::Vec3f direc = CAMERA.getRay().getDirection();
	for (auto& it : boss) {
		//ボスの行列を生成
		ci::Matrix44f mat = ci::Matrix44f::createTranslation(it->getPos()) * ci::Matrix44f::createRotation(it->getRotate());
		mat.invert();
		//Rayをボスの行列をかけてずらす
		CAMERA.getRay().setOrigin(mat * orig);
		CAMERA.getRay().setDirection(mat.transformVec(direc));
		//当たり判定をしてintersectをもらう
		float z = rayToMeshCollision(CAMERA.getRay(), result, it->getVertices(), it->getIndices());
		//そのままでは行列でずれた状態なので戻してから
		//ポジション変換
		CAMERA.getRay().setOrigin(orig);
		CAMERA.getRay().setDirection(direc);
		result = CAMERA.getRay().calcPosition(z);

		if (returnBoxToRayPoint(it->getPos(), it->getSize(), result)) {
			for (auto weapon : weapons) {

				if (weapon->isTrigger()) {
					if (it->getHp() < 0) continue;
					it->Damage(weapon->getAttack());
					for (int i = 0; i < 4; i++) {
						perticle.push_back(std::make_shared<Perticle>(result, ci::Vec3f(0.1, 0.1, 0.1), ci::Vec3f(0, 0, 0), "", ""));
					}
					break;
				}
			}
		}
	}

	CAMERA.getRay().setOrigin(orig);
	CAMERA.getRay().setDirection(direc);
}

void GameMain::bossIsDead()
{
	for (auto& it : boss) {
		if (it->getHp() <= 0)
			boss_dead = true;
	}
}

void GameMain::bossDead()
{
	if (!boss_dead) return;

	dead_count++;
	if (dead_count == 1) {
		SE.find("boss_scream")->start();
	}
	if (dead_count == 1 ||
		dead_count == 60 ||
		dead_count == 100 ||
		dead_count == 170) {
		CAMERA.shakeCamera(1.3f, 0.7f);
		SE.find("boss_landing")->start();
		ui->ui_data["Exprode1"]->setActive(true);
		ui->ui_data["Exprode1"]->setActive(false);
	}
	if (dead_count == 230) {
		SE.find("boss_dead")->start();
		boss.clear();
		CAMERA.shakeCamera(1.6f, 3);
		ui->ui_data["Exprode2"]->setActive(true);
	}

	if (dead_count == 400) {
		is_goal = true;
	}
}

bool GameMain::playerDead()
{
	if (!player->isDead()) return false;
	player_dead_count++;
	if (player_dead_count == 1) {
		SE.find("playaer_dead")->start();
	}
	if (player_dead_count == 120) {
		ui->ui_data["Fade"]->setActive(true);
	}
	if (player_dead_count == 240) {
		SE.allStop();
		SE.allCrear();
		SCENE.shift(game::SceneName::RESULT, false);
		return true;
	}
	return false;
}

void GameMain::playerUpdate(const float& delta_time)
{
	////地面とAimの判定
	//rayToMeshCollision(CAMERA.getRay(), result, map->getVertices(), map->getIndices());
	player->update(delta_time);
	player->setPos(rideMap(player->getRideMapRay(), player->getPos(), player->getSize()));


	bossCollision();

	for (auto& it : object) {

		//軽減処理
		//近くにある物体以外は返す
		if (!collisionBoxToBox(player->getPos(), ci::Vec3f(3, 3, 3), it->getPos(), it->getSize())) continue;
		it->update();
		collision(it);
	}

}
void GameMain::enemyUpdate()
{
	bossSpawn();
	if (boss_dead == true) return;
	for (auto& it : object) {
		if (it->getObjectType() == ObjectType::WALL) continue;
		//プレイヤーから遠ければ処理しない
		if (!collisionBoxToBox(player->getPos(), ci::Vec3f(100, 100, 100), it->getPos(), it->getSize())) continue;
		it->update();
		collision(it);
	}
	for (auto& it : boss) {
		it->update();
		it->setPos(rideMap(it->getRideMapRay(), it->getPos(), it->getSize()));
		ui->setBossHP(it->getHp());
		//プレイヤーと接触したらダメージ
		if (collisionBoxToBox(player->getPos(), player->getSize(), it->getPos(), it->getSize())) {
			player->Damage(it->getAttack());
		}
	}
}
void GameMain::weaponUpdate(const float& delta_time)
{
	ui->getWeapon(false);
	for (auto& it : weapons) {
		it->update(delta_time);
		if (collisionBoxToBox(player->getPos(), player->getSize(), it->getPos(), ci::Vec3f(4, 4, 4))) {
			ui->getWeapon(true);
			if (ENV.pushKey(ci::app::KeyEvent::KEY_g)) {
				SE.find("get")->start();
				for (auto& buf : weapons) {
					buf->setDrop(true);
				}
				it->setDrop(false);
			}
		}
		if (it->isDrop())continue;
		ui->muzzleFlash(it->getStatus().muzzle_pos, it->isTrigger());
	}
}
void GameMain::update(const float& delta_time)
{
	uiUpdate(delta_time);
	if (!ui->start()) return;
	if (playerDead()) return;
	if (player->isDead()) return;
	playerUpdate(delta_time);
	enemySpawn();
	weaponUpdate(delta_time);
	for (auto& it : perticle) {
		it->update();
	}
	enemyUpdate();
	bossIsDead();
	bossDead();
	eraseObjects();
	isGoal();
}

void GameMain::eraseObjects()
{
	for (auto it = object.begin(); it != object.end(); it++) {
		if ((is_goal == true ||
			boss_dead == true) &&
			(*it)->getObjectType() == ObjectType::Enemy) {
			object.erase(it);
			break;
		}
		if (!(*it)->isDead()) continue;
		player->addHp();
		ui->addKills();
		object.erase(it);
		break;
	}
	for (auto it = perticle.begin(); it != perticle.end(); it++) {
		if ((*it)->isDead()) {
			perticle.erase(it);
			break;
		}
	}
}

void GameMain::draw()
{
	ci::gl::clear(ci::ColorA8u(1, 1, 1, 1));
	light->setAmbient(ci::Color(1.0f, 1.0f - player->getColorR(), 1.0f - player->getColorR()));
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
	for (auto& it : perticle) {
		it->draw();
	}

	for (auto& it : goal) {
		it->draw();
	}
	for (auto& it : boss) {
		it->draw();
	}
	map->draw();
	drawSkyDome();
	light->disable();

	ci::gl::disable(GL_LIGHTING);
	CAMERA.draw2d();
	ui->draw();
	shift();
}

void GameMain::shift()
{

}

void GameMain::drawSkyDome()
{
	glCullFace(GL_FRONT);
	skydome->draw();
	glCullFace(GL_BACK);
}

