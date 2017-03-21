#pragma once
#include "../MaterialBase.h"
#include "cinder/TriMesh.h"  
enum class WeaponType {
	Deagle = 0,
	AK = 1,
	Tompson = 2,
	PK = 3
};

struct WeaponStatus {
	int attack_point;
	float rate;
	float relord_time;
	int bullets;
	int max_bullets;
	float scatter;
	float relord_motion;
	ci::Vec2f muzzle_pos;
	ci::Vec3f matrix_t;
	ci::Vec3f matrix_r;
};

struct WeaponMotion {
	bool trigger;
	bool relord;
	float rate;
	float relord_time;
	float relord_motion;
	float rotation;
	float scatter;
};

class WeaponBase : public MaterialBase
{
protected:
	ci::TriMesh mesh;
	WeaponStatus status;
	WeaponMotion motion;
	WeaponType weapon_type;

	//ÉJÉÅÉâÇ©ÇÁå©ÇƒéËÇÃà íuÇ…çáÇÌÇπÇÈÇΩÇﬂÇÃçsóÒ
	ci::Matrix44f matrix;

	bool drop;

	virtual void loading() {}
	virtual void materialSetup() {}
	virtual void statusInit() {}
	virtual void motionReset() {}

	virtual void fire(const float& delta_time);
	virtual void relordMotion(const float& delta_time);
	virtual void drawHaveWeapon();
	virtual void drawDropWeapon();
public:


	WeaponBase(const ci::Vec3f& _pos, const ci::Vec3f& _size,
		const ci::Vec3f& _angle, const std::string& _name,
		const std::string& _path)
		: MaterialBase(_pos, _size, _angle, _name, _path) {}

	WeaponType getWeapon() {
		return weapon_type;
	}
	ci::Vec3f getSize() {
		return ci::Vec3f(4, 4, 4);
	}
	const WeaponStatus& getStatus() {
		return status;
	}
	const bool& isDrop() {
		return drop;
	}
	void setDrop(bool value) {
		drop = value;
	}
	const int& getBullets() {
		return status.bullets;
	}
	const bool& isTrigger() {
		return motion.trigger;
	}
	const int& getAttack() {
		return status.attack_point;
	}
	void setActive(WeaponType wep) {
		if (weapon_type == wep) {
			drop = false;
		}
		else if (weapon_type != wep) {
			drop = true;
		}
	}
	void update(const float& delta_time) override;
	void draw() override;
};
