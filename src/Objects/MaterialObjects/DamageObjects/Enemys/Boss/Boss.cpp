#include "Boss.h"
#include "../../../../../Utility/Texture.h"
#include <random>
#include "../../../../Camera/Camera.h"
#include "../../../../../Utility/SoundManager.h"



void Boss::jump()
{
	jump_count++;
	//１フレーム目はジャンプ
	if (jump_count == 1) {
		gravity = -0.15f;
		vec = 0.01f;
	}

	//着地するくらいで当たり判定を出す
	if (gravity > 0.2f ||
		gravity < 0.3f) {
		attack_size = size * ci::Vec3f(3,0.3f,3);
	}
}

void Boss::dash()
{

}



void Boss::selectBehavior()
{
	behavior_count--;
	if (behavior_count < 0) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> e_type(0, 2);
		enemy_behavior_state = e_type(mt);
		behavior_count = 300;
		motion.move_left_leg = 0;
		motion.move_right_leg = 0;
	}
}

void Boss::behavior()
{
	attack_pos = pos;
	attack_size = size;
	switch (enemy_behavior_state)
	{
	case 0:
		trackingToPlayer();
		break;
	case 1:
		jump();
		break;
	case 2:
		trackingToPlayer();
		break;
	}

}


void Boss::drawBody()
{
	ci::gl::pushModelView();

	TEX.get(name).enableAndBind();
	ci::gl::translate(pos);
	ci::gl::rotate(rotate);
	if (hp < 0) {
		ci::gl::rotate(ci::Vec3f(0, 0, dead_motion));
	}
	material.apply();
	ci::gl::draw(body);
	TEX.get(name).disable();

	ci::gl::popModelView();
}
void Boss::drawLeftLeg()
{
	ci::gl::pushModelView();
	ci::gl::translate(pos);
	ci::gl::rotate(ci::Vec3f(180, motion.angle * 180 / M_PI, motion.move_left_leg));
	ci::gl::translate(ci::Vec3f(0, 0, -0.5));
	TEX.get(leg_name).enableAndBind();
	ci::gl::scale(status.scale);
	material.apply();
	ci::gl::draw(left_leg);
	TEX.get(leg_name).disable();

	ci::gl::popModelView();
}

void Boss::drawRightLeg()
{
	ci::gl::pushModelView();
	ci::gl::translate(pos);
	ci::gl::rotate(ci::Vec3f(180, motion.angle * 180 / M_PI, motion.move_right_leg));
	ci::gl::translate(ci::Vec3f(0, 0, 0.5));
	TEX.get(leg_name).enableAndBind();
	ci::gl::scale(status.scale);
	material.apply();
	ci::gl::draw(right_leg);
	TEX.get(leg_name).disable();
	ci::gl::popModelView();
}


Boss::Boss(const ci::Vec3f & _pos,
	const ci::Vec3f & _size,
	const ci::Vec3f & _rotate,
	const std::string & _name,
	const std::string & _body_path,
	const std::string & _leg_name,
	const std::string & _leg_path,
	ci::TriMesh _body,
	ci::TriMesh _left_leg,
	ci::TriMesh _right_leg)
	: EnemyBase(_pos, _size, _rotate, _name, _body_path,
		_leg_name, _leg_path, _body, _left_leg, _right_leg)
{
	TEX.set(_name, _body_path);
	TEX.set(leg_name, _leg_path);
	SE.registerBufferPlayerNode("boss_walk", "Sound/SE/FormatFactorysmall_explosion.mp3");

	material = ci::gl::Material(ci::ColorA(1, 1, 1, 1.0f),
		ci::ColorA(0.8f, 0.8f, 0.8f, 1.0f),
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f),
		80.0f,
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));

	hp = 20000;

	motion.move_left_leg = 0;
	motion.move_right_leg = 0;
	motion.angle = 0.0f;
	motion.count = 0;
	motion.leg_inc = 0;
	motion.rotate_interval = 30;
	status.speed = 0.2f;
	status.attack = 10;
	status.scale = ci::Vec3f(0.25, 0.4, 0.25);

	enemy_behavior_state = 0;
	jump_count = 0;
	behavior_count = 300;
	vertices = body.getVertices();
	indices = body.getIndices();
}


void Boss::trackingToPlayer()
{
	walk();
	motion.count++;

	if (motion.count == motion.rotate_interval) {
		motion.angle = atan2f(pos.z - CAMERA.getPos().z, pos.x - CAMERA.getPos().x);
		motion.count = 0;
		CAMERA.shakeCamera(0.3f, 0.4f);
		SE.find("boss_walk")->start();
	}

	pos.x -= (cos(motion.angle) * status.speed);
	pos.z -= (sin(motion.angle) * status.speed);
}
void Boss::update()
{
	selectBehavior();
	behavior();
	ObjectBase::update();
	DamageObject::damageUpdate();
	rotate = ci::Vec3f(0, -(90 * M_PI / 180 + motion.angle) * 180 / M_PI, 0);
	box = std::make_shared<ci::AxisAlignedBox3f>(pos - size / 2, pos + size / 2);
}

void Boss::draw()
{
	EnemyBase::draw();
	ci::gl::drawStrokedCube(pos, size);
}
