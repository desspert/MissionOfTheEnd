#pragma once
#include "../MaterialBase.h"

class DamageObject : public MaterialBase
{
protected:
	float color_r = 0;
	float color_a = 1;
public:
	DamageObject(const ci::Vec3f & _pos,
		const ci::Vec3f & _size,
		const ci::Vec3f & _rotate,
		const std::string& _name,
		const std::string& _path);

	void Damage(const int& damage) override;
	void damageUpdate();
	bool isDead() override;
};