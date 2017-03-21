#include "DamageObjects.h"
#include "../../../Utility/Easing/Easing.h"
DamageObject::DamageObject(const ci::Vec3f & _pos,
	const ci::Vec3f & _size,
	const ci::Vec3f & _rotate,
	const std::string& _name,
	const std::string& _path)
	: MaterialBase(_pos, _size, _rotate, _name, _path){
}
void DamageObject::Damage(const int & damage)
{
	hp -= damage;
	color_r = 1.0f;

}

void DamageObject::damageUpdate()
{
	color_r -= 0.3f;
	if (color_r < 0) {
		color_r = 0;
	}
	material.setAmbient(ci::ColorA8u(ci::ColorA(1, 1 - color_r, 1 - color_r, 1.0f)));
}

bool DamageObject::isDead()
{
	if (hp <= 0) {
		dead_motion +=3;
		if (dead_motion > 90) {
			return true;
		}
	}
	return false;
}
