#include "Cube.h"
#include "../../../Utility/Texture.h"
Cube::Cube(const ci::Vec3f& _pos, const ci::Vec3f& _size, const ci::Vec3f& _rotate,
	std::string _name, std::string _path)
	: MaterialBase(_pos, _size, _rotate, _name, _path) {
	TEX.set(_name, _path);
	box = std::make_shared<ci::AxisAlignedBox3f>(pos - size / 2, pos + size / 2);
}

void Cube::update()
{
	ObjectBase::update();
}

void Cube::draw()
{

	ci::gl::pushModelView();
	ci::gl::translate(pos);
	ci::gl::rotate(rotate);
	material.apply();
	TEX.get(name).enableAndBind();
	ci::gl::drawCube(ci::Vec3f(0.0f, 0.0f,0.0f), size);
	TEX.get(name).disable();
	ci::gl::popModelView();
}

