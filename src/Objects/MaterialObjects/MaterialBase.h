#pragma once
#include "../ObjectBase.h"
#include "cinder/gl/Material.h"

class MaterialBase : public ObjectBase {
protected:
	std::string name;
	ci::gl::Material material;
public:
	MaterialBase(const ci::Vec3f& _pos, const ci::Vec3f& _size,
		const ci::Vec3f& _rotate, const std::string& _name, const std::string& _path);
	void setup() override;
};