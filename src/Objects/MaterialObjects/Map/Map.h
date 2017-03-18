#pragma once
#include "../MaterialBase.h"
#include "cinder/TriMesh.h"  
#include <unordered_map>
class Map : public MaterialBase
{
private:
	ci::TriMesh mesh;
public:
	Map(const ci::Vec3f& _pos, const ci::Vec3f& _size,
		const ci::Vec3f& _rotate, const std::string& _name, 
		const std::string& _path,
		const std::string& _obj_path);
	void draw() override;
};