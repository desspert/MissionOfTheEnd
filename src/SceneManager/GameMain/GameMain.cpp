#include "GameMain.h"
#include "../../Utility/SoundManager.h"
#include "../../Objects/MaterialObjects/Cube/Cube.h"
#include "../../Objects/MaterialObjects/Sphere/Sphere.h"
#include "../../Objects/Camera/Camera.h"
#include "../../Objects/MaterialObjects/DamageObjects/Player/Player.h"
#include "../../Objects/MaterialObjects/Map/Map.h"
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
			// 5. Œð·”»’è‚Å“¾‚ç‚ê‚½ZÀ•W‚©‚çAXYZ‚ð‹‚ß‚é
			//    Ray::calcPosition ‚ªŽg‚¦‚é
			result = ray.calcPosition(z);
			break;
		}
	}
}
void rayToAABBCollision(std::shared_ptr<ObjectBase>& obj, ci::Ray ray, ci::Vec3f& result) {
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
		result = ray.calcPosition(*itr);
	}
	else {
		result = ci::Vec3f(1000, 1000, 1000);
	}
}

void GameMain::mapObjectsSetup()
{
	res = std::make_shared<Sphere>(ci::Vec3f(0, 0, 0), ci::Vec3f(0.1f, 0.1f, 0.1f), ci::Vec3f(0, 0, 0), "jimen", "Objects/Wall/039.jpg");
	skydome = std::make_shared<Sphere>(ci::Vec3f(0, 0, 0), ci::Vec3f(1000, 1000, 1000), ci::Vec3f(0, 0, 0), "skydome", "Objects/SkyDome/Skydome151004y.jpg");
	player = std::make_shared<Player>(ci::Vec3f(0, 10, 4), ci::Vec3f(1, 6, 1), ci::Vec3f(0, 0, 0));

	object.push_back(std::make_shared<Cube>(ci::Vec3f(0, 1, 4), ci::Vec3f(1, 1, 1), ci::Vec3f(0, 0, 0), "jimen", "Objects/Wall/039.jpg"));

	object.push_back(std::make_shared<Map>(ci::Vec3f(0, -3, 4), ci::Vec3f(100, 10, 100), ci::Vec3f(0, 0, 0), "map", "Objects/Map/20141130172655.jpg", "Objects/Map/terrain.obj"));

	player->setup();
	skydome->setup();
	res->setup();
	for (auto& it : object) {
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
void GameMain::update(const float& delta_time)
{
	player->update();
	for (auto& it : object) {
		it->update();
		if ((it->getAABB()) != nullptr) {
			rayToAABBCollision(it, CAMERA.getRay(), result);
		}
		if (it->getVertices().size() != 0) {
			rayToMeshCollision(CAMERA.getRay(), result, it->getVertices(), it->getIndices());
			rayToMeshCollision((*player->getRideMapRay()), result2, it->getVertices(), it->getIndices());
			
			if (result2.y > player->getPos().y - player->getSize().y) {
				player->setPos(ci::Vec3f(player->getPos().x, result2.y + player->getSize().y, player->getPos().z));
			}
		}
		res->setPos(result);
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

