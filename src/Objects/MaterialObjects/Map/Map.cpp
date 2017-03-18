#include "Map.h"
#include "../../../Utility/Texture.h"
#include "cinder/ObjLoader.h"
Map::Map(const ci::Vec3f& _pos, const ci::Vec3f& _size, const ci::Vec3f& _rotate,
	const std::string& _name, const std::string& _path, const std::string& _obj_path)
	: MaterialBase(_pos, _size, _rotate, _name, _path) {
	TEX.set(_name, _path);

	ci::ObjLoader loader = ci::ObjLoader(ci::app::loadAsset(_obj_path));

	loader.load(&mesh, boost::logic::indeterminate, boost::logic::indeterminate, false);


	vertices = mesh.getVertices();
	indices = mesh.getIndices();
}

void Map::draw()
{

	ci::gl::pushModelView();
	material.apply();
	TEX.get(name).enableAndBind();
	ci::gl::draw(mesh);
	TEX.get(name).disable();
	ci::gl::popModelView();

}

