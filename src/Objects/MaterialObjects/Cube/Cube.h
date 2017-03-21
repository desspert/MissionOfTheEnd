#pragma once
#include "../MaterialBase.h"

class Cube : public MaterialBase
{
public:
	Cube(const ci::Vec3f& _pos, const ci::Vec3f& _size, 
		const ci::Vec3f& _rotate, const std::string& _name, const std::string& _path);
	void update() override;
	void draw() override;
};