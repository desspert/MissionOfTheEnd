#include "Player.h"
#include "../../../Camera/Camera.h"
#include "../../../../Utility/Input/Input.h"
Player::Player(const ci::Vec3f & _pos,
	const ci::Vec3f & _size,
	const ci::Vec3f & _rotate,
	const std::string& _name,
	const std::string& _path)
	: DamageObject(_pos, _size, _rotate,_name,_path)
{
	CAMERA.setPos(_pos);
}

void Player::setup()
{
	CAMERA.setup();
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
	pos.y -= 2;
}

void Player::update()
{
	move();
	CAMERA.update();
	CAMERA.setPos(pos);
	ObjectBase::update();
}

void Player::draw()
{
	CAMERA.draw();
}
