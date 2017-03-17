#pragma once
#include "../MaterialBase.h"
#include "cinder/TriMesh.h"  
enum class Weapon {
	Deagle = 0,
	AK = 1,
	Tompson = 2,
	MG = 3
};

struct WeaponStatus {
	int attack_point;
	int rate;
	int bullets;
	//ƒTƒu’e–ò
	int reserve;
	float scatter;
	bool trigger;
	bool relord;
};

class WeaponBase : public MaterialBase
{
protected:
	ci::TriMesh mesh;
	WeaponStatus status;
	bool active;
	Weapon weapon;
	int relord_time;
	//Anim<float>	re_motion;
	float rotation;
public:


	WeaponBase(const ci::Vec3f& _pos, const ci::Vec3f& _size,
		const ci::Vec3f& _angle, const std::string& _name,
		const std::string& _path)
		: MaterialBase(_pos, _size, _angle, _name, _path) {

	}

	float getEndMotion() {

	}
	Weapon getWeapon() {
		return weapon;
	}
	virtual void  fire() = 0;
	virtual void Relord() = 0;
	const WeaponStatus& getStatus() {
		return status;
	}
	bool getActive() {
		return active;
	}
	void setActive(Weapon wep) {
		if (weapon == wep) {
			active = true;
		}
		else if (weapon != wep) {
			active = false;
		}
	}
};
