#include "BreakWall.h"
#include "../../../../Utility/Texture.h"
BreakWall::BreakWall(const ci::Vec3f & _pos,
	const ci::Vec3f & _size,
	const ci::Vec3f & _rotate,
	const std::string& _name,
	const std::string& _path,
	const int& _hp)
	: DamageObject(_pos, _size, _rotate, _name, _path)
{
	TEX.set(_name, _path);
	box = std::make_shared<ci::AxisAlignedBox3f>(pos - size / 2, pos + size / 2);
	hp = _hp;
	object_type = ObjectType::BREAKWALL;
}
void BreakWall::update()
{
	box = std::make_shared<ci::AxisAlignedBox3f>(pos - size / 2, pos + size / 2);
}
void BreakWall::draw()
{
	DamageObject::damageUpdate();
	ci::gl::pushModelView();
	TEX.get(name).enableAndBind();
	material.apply();
	ci::gl::drawCube(pos, size);
	TEX.get(name).disable();
	ci::gl::popModelView();
}
bool DamageObject::isDead()
{
	if (hp <= 0) {
		return true;
	}
	return false;
}