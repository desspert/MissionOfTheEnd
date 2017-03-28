#include "Player.h"
#include "../../../Camera/Camera.h"
#include "../../../../Utility/Input/Input.h"
#include "../../../../Utility/SoundManager.h"
Player::Player(const ci::Vec3f & _pos,
	const ci::Vec3f & _size,
	const ci::Vec3f & _rotate,
	const std::string& _name,
	const std::string& _path)
	: DamageObject(_pos, _size, _rotate, _name, _path)
{
	CAMERA.setPos(_pos);
	walk_count = 0;
}

void Player::Damage(const int & damage) {
	if (damage_count < 0) {
		if (damage < 20) {
			SE.find("playaer_damage1")->start();
			SE.find("playaer_voice1")->start();
		}
		if (damage > 20) {
			SE.find("playaer_damage2")->start();
			SE.find("playaer_voice2")->start();
		}
		hp -= damage;
		color_r = 1.0f;
		damage_count = 1.0f;
	}
}

void Player::setup()
{
	damage_count = 0;
	hp = 100;
	SE.registerBufferPlayerNode("playaer_damage1", "Sound/SE/Player/damage1.mp3");
	SE.registerBufferPlayerNode("playaer_damage2", "Sound/SE/Player/damage2.mp3");
	SE.registerBufferPlayerNode("playaer_voice1", "Sound/SE/Player/game-wizard-damage1.mp3");
	SE.registerBufferPlayerNode("playaer_voice2", "Sound/SE/Player/game-wizard-damage2.mp3");
	SE.registerBufferPlayerNode("playaer_dead", "Sound/SE/Player/game-swordman-death1.mp3");
	SE.registerFilePlayerNode("playaer_walk", "Sound/SE/Player/hito_ge_run_tsuti01.mp3");
}
void Player::jump()
{

	if (gravity > 0.99f) {
		if (ENV.pushKey(ci::app::KeyEvent::KEY_SPACE)) {
			gravity = -0.15f;
			vec = 0.01f;
		}
	}
	gravityApply();
}
void Player::move()
{
	if (ENV.pressKey(ci::app::KeyEvent::KEY_w)) {
		pos += ci::Vec3f(0.2f*sin(CAMERA.getCameraAngle().x), 0.0f, 0.2f*cos(CAMERA.getCameraAngle().x));
	}
	if (ENV.pressKey(ci::app::KeyEvent::KEY_a)) {
		pos.x += 0.2f*cos(CAMERA.getCameraAngle().x);
		pos.z -= 0.2f*sin(CAMERA.getCameraAngle().x);
	}
	if (ENV.pressKey(ci::app::KeyEvent::KEY_s)) {
		pos -= ci::Vec3f(0.2f*sin(CAMERA.getCameraAngle().x), 0.0f, 0.2f*cos(CAMERA.getCameraAngle().x));
	}
	if (ENV.pressKey(ci::app::KeyEvent::KEY_d)) {
		pos.x -= 0.2f*cos(CAMERA.getCameraAngle().x);
		pos.z += 0.2f*sin(CAMERA.getCameraAngle().x);
	}
	jump();
}

void Player::walk()
{
	if (ENV.pressKey(ci::app::KeyEvent::KEY_w)||
		ENV.pressKey(ci::app::KeyEvent::KEY_a) ||
		ENV.pressKey(ci::app::KeyEvent::KEY_s) ||
		ENV.pressKey(ci::app::KeyEvent::KEY_d)) {
		walk_count++;
	}
	else {
		walk_count = 0;
		SE.find("playaer_walk")->stop();
	}
	if (walk_count == 1) {
		SE.find("playaer_walk")->start();
		SE.find("playaer_walk")->setLoopEnabled(true);
	}
	
}

void Player::update(const float& delta_time)
{
	damage_count -= delta_time;
	DamageObject::damageUpdate();
	walk();
	move();
	CAMERA.update();
	CAMERA.setPos(pos);
	ObjectBase::update();
}

void Player::draw()
{
	CAMERA.draw();
}

bool Player::isDead()
{
	if (hp <= 0) {
		return true;
	}
	return false;
}
