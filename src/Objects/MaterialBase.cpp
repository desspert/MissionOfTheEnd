#include "Cube.h"
#include "../../../Texture.h"
Cube::Cube(const ci::Vec3f& _pos, const ci::Vec3f& _size, const ci::Vec3f& _rotate,
	std::string name, std::string path)
	: ObjectBase(_pos, _size, _rotate) {
	TEX.set(name, path);
	this->name = name;
}

void Cube::update()
{
	//box = std::make_shared<AxisAlignedBox3f>(pos - size / 2, pos + size / 2);

}

void Cube::draw()
{

	ci::gl::pushModelView();
	ci::gl::rotate(rotate);
	material.apply();
	TEX.get(name).enableAndBind();
	ci::gl::drawCube(pos, size);
	TEX.get(name).disable();
	ci::gl::popModelView();
}

void Cube::setup()
{
	material = ci::gl::Material(ci::ColorA(1, 1, 1, 1.0f),    // 環境光が当たった時の色
		ci::ColorA(0.8f, 0.8f, 0.8f, 1.0f),    // 拡散光が当たった時の色
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f),    // 鏡面光が当たった時の色
		80.0f,                             // 鏡面反射の鋭さ(値が大きいほど鋭くなる)
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));   // 自己発光色
}

