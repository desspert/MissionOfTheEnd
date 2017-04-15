#pragma once
#include "../MaterialBase.h"

class Perticle : public MaterialBase
{
private:
	ci::Vec3f move_vec;
	int count;
public:
	Perticle(const ci::Vec3f& _pos, const ci::Vec3f& _size,
		const ci::Vec3f& _rotate, const std::string& _name, const std::string& _path);
	
	void setColor(const ci::Vec3f& color) {
		material = ci::gl::Material(ci::ColorA(color.x, color.y, color.z, 1.0f),
			ci::ColorA(color.x, color.y, color.z, 1.0f),
			ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f),
			10.0f,
			ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));
	}
	
	void update() override;
	void draw() override;
};