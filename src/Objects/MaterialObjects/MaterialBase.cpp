#include "MaterialBase.h"
MaterialBase::MaterialBase(const ci::Vec3f & _pos, 
	const ci::Vec3f & _size,
	const ci::Vec3f & _rotate, 
	const std::string& _name,
	const std::string& _path)
: ObjectBase(_pos, _size, _rotate),name(_name) {
}

void MaterialBase::setup()
{
	material = ci::gl::Material(ci::ColorA(1, 1, 1, 1.0f),    // ŠÂ‹«Œõ
		ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),    // ŠgUŒõ
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f),    // ‹¾–ÊŒõ
		80.0f,                             // ‹¾–Ê”½Ë
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));   // ©ŒÈ”­ŒõF
}

void MaterialBase::gravityApply()
{
	if (gravity < 1) {
		vec *= 1.01f;
		gravity += vec;
	}
	if (gravity > 0.2f) {
		pos.y -= 0.2f;
	}
	else {
		pos.y -= gravity;
	}
	
}

