#pragma once
#include "../MaterialBase.h"

class Goal : public MaterialBase
{
public:
	Goal(const ci::Vec3f& _pos, const ci::Vec3f& _size,
		const ci::Vec3f& _rotate, const std::string& _name, const std::string& _path);
	void setup() override;
	void update() override;
	void draw() override;
};