#include "Boss.h"
#include "../../../../../Utility/Texture.h"
#include <random>
#include "../../../../Camera/Camera.h"
#include "../../../../../Utility/SoundManager.h"
#include "../../../../../Utility/Easing/Easing.h"


void Boss::jump()
{
	jump_count++;
	//１フレーム目はジャンプ
	if (jump_count == 1) {
		gravity = -0.6f;
		vec = 0.01f;
	}
	//空中でプレイヤーの地点まで移動
	if (gravity > -0.2f &&
		gravity < 0.5f) {
		motion.angle = atan2f(pos.z - CAMERA.getPos().z, pos.x - CAMERA.getPos().x);
		pos.x -= (cos(motion.angle)*1.5f);
		pos.z -= (sin(motion.angle)*1.5f);
	}
	//着地
	if (gravity > 0.98f &&
		gravity < 1) {
		CAMERA.shakeCamera(1, 1);
		SE.find("boss_landing")->start();
	}
	gravityApply();
}

void Boss::dash()
{
	dash_count++;
	material.setAmbient(ci::ColorA(dash_motion_color, dash_motion_color, 1));
	//プレイヤーに向く
	if (dash_count == 1) {
		motion.angle = atan2f(pos.z - CAMERA.getPos().z, pos.x - CAMERA.getPos().x);
		//青く点滅
		c_Easing::apply(dash_motion_color, 1, EasingFunction::Linear, 7);
		c_Easing::apply(dash_motion_color, 0, EasingFunction::Linear, 7);
		c_Easing::apply(dash_motion_color, 1, EasingFunction::Linear, 7);
		c_Easing::apply(dash_motion_color, 0, EasingFunction::Linear, 7);
		c_Easing::apply(dash_motion_color, 1, EasingFunction::Linear, 7);
		c_Easing::apply(dash_motion_color, 0, EasingFunction::Linear, 7);
		c_Easing::apply(dash_motion_color, 1, EasingFunction::Linear, 7);
		SE.find("boss_effect")->start();
	}
	if (dash_count == 60) {
		SE.find("boss_dash")->start();
	}
	if (dash_count > 60&&
		dash_count < 90) {
		pos.x -= (cos(motion.angle)*3);
		pos.z -= (sin(motion.angle)*3);

	}
	if (dash_count > 120) {
		behavior_count = 0;
		material.setAmbient(ci::ColorA(1, 1, 1));
	}
	gravityApply();
}



void Boss::selectBehavior()
{
	behavior_count--;
	if (behavior_count < 0) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> e_type(0, 2);
		enemy_behavior_state = e_type(mt);
		behavior_count = 200;
		jump_count = 0;
		dash_count = 0;
		motion.move_left_leg = 0;
		motion.move_right_leg = 0;
	}
}

void Boss::behavior()
{
	switch (enemy_behavior_state)
	{
	case 0:
		trackingToPlayer();
		break;
	case 1:
		jump();
		break;
	case 2:
		dash();
		break;
	}

}


void Boss::drawBody()
{
	ci::gl::pushModelView();

	TEX.get(name).enableAndBind();
	ci::gl::translate(pos);
	ci::gl::rotate(rotate);
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
	material = ci::gl::Material(ci::ColorA(1, 1, 1, 1.0f),
		ci::ColorA(0.8f, 0.8f, 0.8f, 1.0f),
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f),
		80.0f,
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));

	hp = 10000;

	motion.move_left_leg = 0;
	motion.move_right_leg = 0;
	motion.angle = 0.0f;
	motion.count = 0;
	motion.leg_inc = 0;
	motion.rotate_interval = 30;
	status.speed = 0.16f;
	status.attack = 30;
	status.scale = ci::Vec3f(0.25, 0.4, 0.25);

	enemy_behavior_state = 0;
	jump_count = 0;
	dash_count = 0;
	dash_motion_color = 0;
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
	behavior();
	selectBehavior();
	ObjectBase::update();
	DamageObject::damageUpdate();
	rotate = ci::Vec3f(0, -(90 * M_PI / 180 + motion.angle) * 180 / M_PI, 0);
	box = std::make_shared<ci::AxisAlignedBox3f>(pos - size / 2, pos + size / 2);
}

void Boss::draw()
{
	drawBody();
	drawLeftLeg();
	drawRightLeg();
}
