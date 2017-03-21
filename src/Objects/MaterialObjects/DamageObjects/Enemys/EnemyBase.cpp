#include "EnemyBase.h"
#include "../../../../Utility/Texture.h"
#include "../../../Camera/Camera.h"
EnemyBase::EnemyBase(const ci::Vec3f & _pos,
	const ci::Vec3f & _size,
	const ci::Vec3f & _rotate,
	const std::string& _name,
	const std::string& _body_path,
	const std::string& _leg_name,
	const std::string& _leg_path,
	ci::TriMesh _body,
	ci::TriMesh _left_leg,
	ci::TriMesh _right_leg)
	: DamageObject(_pos, _size, _rotate, _name, _body_path)
	, leg_name(_leg_name),body(_body), 
	left_leg(_left_leg), right_leg(_right_leg){
	object_type = ObjectType::Enemy;
}

void EnemyBase::trackingToPlayer()
{
	motion.count++;
	
	if (motion.count == motion.rotate_interval) {
		motion.angle = atan2f(pos.z - CAMERA.getPos().z, pos.x - CAMERA.getPos().x);
		motion.count = 0;
	}

	pos.x -= (cos(motion.angle) * status.speed);
	pos.z -= (sin(motion.angle) * status.speed);
}

void EnemyBase::walk()
{
	motion.leg_inc += 0.1;
	motion.move_left_leg = (sin(motion.leg_inc)) * 60;
	motion.move_right_leg = ((sin(motion.leg_inc - 3)) * 60);
	gravityApply();
}

void EnemyBase::update()
{
	ObjectBase::update();
	DamageObject::damageUpdate();
	walk();
	trackingToPlayer();
	box = std::make_shared<ci::AxisAlignedBox3f>(pos - size / 2, pos + size / 2);
}

void EnemyBase::drawBody()
{
	ci::gl::pushModelView();

	TEX.get(name).enableAndBind();
	ci::gl::translate(pos - ci::Vec3f(0, 0.5, 0));
	ci::gl::rotate(ci::Vec3f(0, -(90 * M_PI / 180 + motion.angle) * 180 / M_PI, 0));
	if (hp < 0) {
		ci::gl::rotate(ci::Vec3f(0, 0, dead_motion));
	}
	ci::gl::scale(status.scale);
	material.apply();
	ci::gl::draw(body);
	TEX.get(name).disable();

	ci::gl::popModelView();

}

void EnemyBase::drawLeftLeg()
{
	ci::gl::pushModelView();

	ci::gl::translate(pos - ci::Vec3f(-0.06, 0, 0.08));
	ci::gl::rotate(ci::Vec3f(180, motion.angle * 180 / M_PI, motion.move_left_leg));
	TEX.get(leg_name).enableAndBind();
	ci::gl::scale(status.scale);
	material.apply();
	ci::gl::draw(left_leg);
	TEX.get(leg_name).disable();

	ci::gl::popModelView();
}

void EnemyBase::drawRightLeg()
{
	ci::gl::pushModelView();
	ci::gl::translate(pos - ci::Vec3f(-0.06, 0, -0.08));
	ci::gl::rotate(ci::Vec3f(180, motion.angle * 180 / M_PI, motion.move_right_leg));
	TEX.get(leg_name).enableAndBind();
	ci::gl::scale(status.scale);
	material.apply();
	ci::gl::draw(right_leg);
	TEX.get(leg_name).disable();
	ci::gl::popModelView();
}


void EnemyBase::draw()
{
	drawBody();
	if (hp < 0)return;
	drawLeftLeg();
	drawRightLeg();
}
