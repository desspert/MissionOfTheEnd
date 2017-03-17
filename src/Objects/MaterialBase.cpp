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
	material = ci::gl::Material(ci::ColorA(1, 1, 1, 1.0f),    // �����������������̐F
		ci::ColorA(0.8f, 0.8f, 0.8f, 1.0f),    // �g�U���������������̐F
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f),    // ���ʌ��������������̐F
		80.0f,                             // ���ʔ��˂̉s��(�l���傫���قǉs���Ȃ�)
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));   // ���Ȕ����F
}

