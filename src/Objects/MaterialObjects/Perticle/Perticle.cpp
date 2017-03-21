#include "Perticle.h"
#include<random>
Perticle::Perticle(const ci::Vec3f& _pos, const ci::Vec3f& _size,
	const ci::Vec3f& _rotate, const std::string& _name, const std::string& _path)
	: MaterialBase(_pos, _size, _rotate, _name, _path) {
	material = ci::gl::Material(ci::ColorA(1, 0, 0, 1.0f),
		ci::ColorA(0.8f, 0.0f, 0.0f, 1.0f),
		ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f),
		10.0f,
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> pos_random(-0.1f, 0.1f);
	move_vec.x = pos_random(mt);
	move_vec.z = pos_random(mt);
	move_vec.y = -0.05f;
	count = 0;
}

void Perticle::update()
{
	count++;
	if (count == 30) {
		arrive = false;
	}
	pos -= move_vec;
	gravityApply();
}

void Perticle::draw()
{

	ci::gl::pushModelView();
	ci::gl::rotate(rotate);
	material.apply();
	ci::gl::drawCube(pos, size);
	ci::gl::popModelView();
}
