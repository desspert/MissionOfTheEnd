#pragma once
#include"../DamageObjects.h"

class BreakWall : public DamageObject
{
public:

	BreakWall(const ci::Vec3f & _pos,
		const ci::Vec3f & _size,
		const ci::Vec3f & _rotate,
		const std::string& _name,
		const std::string& _path,
		const int& _hp);
	void update()override;
	void draw()override;
	bool isDead() override;
};