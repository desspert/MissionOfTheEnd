#include "Player.h"
#include "../../../Camera/Camera.h"
#include "../../../../Utility/Input/Input.h"
Player::Player(const ci::Vec3f & _pos,
	const ci::Vec3f & _size,
	const ci::Vec3f & _rotate,
	const std::string& _name,
	const std::string& _path)
	: DamageObject(_pos, _size, _rotate, _name, _path)
{
	CAMERA.setPos(_pos);
	
}

void Player::setup()
{
	damage_count = 0;
	hp = 300;
}
void Player::jump()
{
	
	/*if (jump_flag == false) {
	if (ENV.pressKey(KeyEvent::KEY_w) ||
	ENV.pressKey(KeyEvent::KEY_a) ||
	ENV.pressKey(KeyEvent::KEY_s) ||
	ENV.pressKey(KeyEvent::KEY_d)) {
	walk++;
	if (walk == 15) {
	SE.buffer_player->setBuffer(SE.getSound("walk"));
	SE.buffer_player->start();
	walk = 0;
	}
	}
	}*/
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

void Player::update(const float& delta_time)
{
	damage_count -= delta_time;
	DamageObject::damageUpdate();
	move();
	CAMERA.update();
	CAMERA.setPos(pos);
	ObjectBase::update();
}

void Player::draw()
{
	CAMERA.draw();
	ci::gl::drawStrokedCube(pos, size);
}
