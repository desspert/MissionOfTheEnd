#pragma once
#include "../MaterialBase.h"
#include "cinder/gl/Material.h"

class Cube : public MaterialBase
{
public:
	Cube(const ci::Vec3f& _pos, const ci::Vec3f& _size, 
		const ci::Vec3f& _rotate, std::string name, std::string path);
	void update() override;
	void draw() override;
};