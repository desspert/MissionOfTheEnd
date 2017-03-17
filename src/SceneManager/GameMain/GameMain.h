#pragma once
#include "../SceneBase.h"
#include "../SceneManager.h"
#include "cinder/gl/Light.h"
class Player;
class ObjectBase;
class Sphere;
 
class GameMain : public SceneBase
{
private:
	std::shared_ptr<Player> player;
	std::list<std::shared_ptr<ObjectBase>> object;
	std::shared_ptr<Sphere> skydome;
	std::shared_ptr<Sphere> res;
	std::shared_ptr<ci::gl::Light> light;
	std::vector<std::function<void()>> function;
	ci::Vec3f result;
	ci::Vec3f result2;
public:
	GameMain();
	
	/*void damage(std::list<std::shared_ptr<ObjectBase>> obj,
		std::list<std::shared_ptr<WeaponBase>> weap, Vec3f ray_point);*/
	//void setUpdate(std::list<std::shared_ptr<ObjectBase>> obj);
	

	//void col();
	void mapObjectsSetup();
	void mapTipSetup();
	void lightSetup();

	void setup() override;
	void update(const float& delta_time) override;
	void draw() override;
	
	void drawSkyDome();
};


