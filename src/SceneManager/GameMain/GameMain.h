#pragma once
#include "../SceneBase.h"
#include "../SceneManager.h"
#include "cinder/gl/Light.h"
#include "cinder/TriMesh.h"
class Player;
class ObjectBase;
class Sphere;
class WeaponBase;
class Spawner;
class Map;
class GameMainUI;
class Perticle;
class Goal;
class Boss;

struct EnemyData {
	EnemyData(const ci::TriMesh& _body, const ci::TriMesh& _left_leg,
		const ci::TriMesh& _right_leg) :body(_body),
		left_leg(_left_leg), right_leg(_right_leg){}

	ci::TriMesh body;
	ci::TriMesh left_leg;
	ci::TriMesh right_leg;
};
struct EnemyPath {
	EnemyPath(
		const std::string& _body_path, 
		const std::string& _leg_path, 
		const std::string& _body_tex_path,
		const std::string& _leg_tex_path)
		: body_path(_body_path), leg_path(_leg_path),
		body_tex_path(_body_tex_path), leg_tex_path(_leg_tex_path) {}
	std::string body_path;
	std::string leg_path;

	std::string body_tex_path;
	std::string leg_tex_path;
};
 
class GameMain : public SceneBase
{
private:
	bool is_goal;
	bool boss_dead;
	int goal_count;

	std::shared_ptr<GameMainUI> ui;

	std::shared_ptr<Player> player;
	std::list<std::shared_ptr<Goal>> goal;
	std::list<std::shared_ptr<ObjectBase>> object;
	std::list<std::shared_ptr<Boss>> boss;
	std::list<std::shared_ptr<Spawner>> spawner;
	std::list<std::shared_ptr<WeaponBase>> weapons;
	std::list<std::shared_ptr<Perticle>> perticle;

	Map* map;
	std::shared_ptr<Sphere> skydome;
	std::shared_ptr<Sphere> res;
	std::shared_ptr<ci::gl::Light> light;
	
	ci::Vec3f result;
	//敵のデータ
	std::vector<EnemyData> enemys_mesh;
	std::vector<EnemyPath> enemys_path;

public:
	GameMain();
	
	void soundSetup();
	void uiSetup();
	void enemysPathAdd();
	void enemysLoading();
	void breakWallSetup();
	void mapObjectsSetup();
	void rideOnTerrain();
	void mapTipSetup(const std::string& map_path);
	void lightSetup();

	void setup() override;
	void resetObjects();
	void bossSetup();

	void rayToAABBCollision(std::shared_ptr<ObjectBase>& obj, ci::Ray ray, ci::Vec3f& result);
	void isGoal();

	ci::Vec3f rideMap(ci::Ray ray, const ci::Vec3f& pos, const ci::Vec3f& size);
	void physicsJudge(std::shared_ptr<ObjectBase>& it);
	void collision(std::shared_ptr<ObjectBase>& it);
	void uiUpdate(const float& delta_time);
	void enemySpawn();
	void bossCollision();
	void playerUpdate(const float& delta_time);
	void weaponUpdate(const float& delta_time);
	void update(const float& delta_time) override;
	void eraseObjects();

	void draw() override;
	void shift();
	void drawSkyDome();
};


