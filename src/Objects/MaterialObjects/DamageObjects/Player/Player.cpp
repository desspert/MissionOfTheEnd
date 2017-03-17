#include "Player.h"
#include "../../../Camera/Camera.h"
#include "../../../../Utility/Input/Input.h"
Player::Player(const ci::Vec3f & _pos, const ci::Vec3f & _size, 
	const ci::Vec3f & _rotate)
	: ObjectBase(_pos, _size, _rotate)
{
	CAMERA.setPos(_pos);
}

void Player::setup()
{
	CAMERA.setup();
	ride_map = std::make_shared<ci::Ray>();
	ride_map->setOrigin(pos + ci::Vec3f(0, size.y, 0));
	ride_map->setDirection(ci::Vec3f(0, -1000, 0));
}

void Player::move()
{
	pos.y-=2;
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
	ride_map->setOrigin(pos);
}

void Player::update()
{
	move();
	CAMERA.update();
	CAMERA.setPos(pos);
	
}

void Player::draw()
{
	CAMERA.draw();
}
