#include "Goal.h"

Goal::Goal(const ci::Vec3f& _pos, const ci::Vec3f& _size, const ci::Vec3f& _rotate,
	const std::string& _name, const std::string& _path)
	: MaterialBase(_pos, _size, _rotate, _name, _path) {
}
void Goal::setup()
{
	material = ci::gl::Material(ci::ColorA(0.5, 1, 0.5, 1.0f),
		ci::ColorA(0.8f, 0.8f, 0.8f, 1.0f),
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f),
		80.0f,                           
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));
}

void Goal::update()
{
	ObjectBase::update();
}

void Goal::draw()
{

	ci::gl::pushModelView();
	ci::gl::translate(pos);
	ci::gl::rotate(rotate);
	material.apply();
	ci::gl::drawCube(ci::Vec3f(0.0f, 0.0f, 0.0f), size);
	ci::gl::popModelView();
}

