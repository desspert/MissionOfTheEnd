#include "Sphere.h"
#include "../../../Utility/Texture.h"
Sphere::Sphere(const ci::Vec3f& _pos, const ci::Vec3f& _size, const ci::Vec3f& _rotate,
	std::string _name, std::string _path)
	: MaterialBase(_pos, _size, _rotate, _name, _path) {
	TEX.set(_name, _path);
}

void Sphere::update()
{
	//box = std::make_shared<AxisAlignedBox3f>(pos - size / 2, pos + size / 2);

}

void Sphere::draw()
{

	ci::gl::pushModelView();
	ci::gl::translate(pos);
	ci::gl::rotate(rotate);
	material.apply();
	TEX.get(name).enableAndBind();
	ci::gl::drawSphere(ci::Vec3f(0.0f, 0.0f,0.0f),size.x,30);
	TEX.get(name).disable();
	ci::gl::popModelView();
}
