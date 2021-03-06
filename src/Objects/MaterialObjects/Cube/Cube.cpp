#include "Cube.h"
#include "../../../Utility/Texture.h"
Cube::Cube(const ci::Vec3f& _pos, const ci::Vec3f& _size, const ci::Vec3f& _rotate,
	const std::string& _name, const std::string& _path)
	: MaterialBase(_pos, _size, _rotate, _name, _path) {
	TEX.set(_name, _path);
	box = std::make_shared<ci::AxisAlignedBox3f>(pos - size / 2, pos + size / 2);
	object_type = ObjectType::WALL;
}
Cube::Cube(const ci::Vec3f& _pos, const ci::Vec3f& _size, const ci::Vec3f& _rotate,
	const std::string& _name, const std::string& _path,const bool& boss_cube)
	: MaterialBase(_pos, _size, _rotate, _name, _path) {
	TEX.set(_name, _path);
	box = std::make_shared<ci::AxisAlignedBox3f>(pos - size / 2, pos + size / 2);
	object_type = ObjectType::BOSSCUBE;
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

