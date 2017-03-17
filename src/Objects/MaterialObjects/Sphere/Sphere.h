#pragma once
#include "../MaterialBase.h"

class Sphere : public MaterialBase
{
public:
	Sphere(const ci::Vec3f& _pos, const ci::Vec3f& _size,
		const ci::Vec3f& _rotate, std::string _name, std::string _path);
	void update() override;
	void draw() override;
};