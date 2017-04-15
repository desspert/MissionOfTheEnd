#include "WeaponBase.h"
#include "../../../Utility/SoundManager.h"
#include "../../../Utility/Input/Input.h"
#include "../../Camera/Camera.h"
#include "../../../Utility/Easing/Easing.h"
#include "../../../Utility/Texture.h"
void WeaponBase::fire(const float& delta_time)
{
	motion.trigger = false;
	if (motion.relord == true) return;
	if (status.bullets <= 0) return;
	if (ENV.pressKey(ci::app::MouseEvent::LEFT_DOWN)) {
		motion.rate -= delta_time;

		if (motion.rate <= 0) {
			SE.find(name)->start();
			status.bullets--;
			CAMERA.cameraScatter(status.scatter);
			motion.scatter = status.scatter;
			motion.trigger = true;
			motion.rate = status.rate;
		}
	}
	if (ENV.pullKey(ci::app::MouseEvent::LEFT_DOWN)) {
		motion.rate = 0;
	}


}

static void tweek(float t, float b, float e, float& r) {
	r = (e - b) * t + b;
}
void WeaponBase::relordMotion(const float& delta_time)
{

	if (status.bullets == status.max_bullets) return;
	
	if (!motion.relord) {
		if (ENV.pushKey(ci::app::KeyEvent::KEY_r) ||
			status.bullets <= 0) {
			motion.relord = true;
			SE.find("relord")->start();
		}
	}
	if (!motion.relord) return;
	

	motion.relord_time += delta_time;

	if (motion.relord_time <= status.relord_time/2) {
		tweek(motion.relord_time /(status.relord_time / 2), 0, status.relord_motion,motion.relord_motion);
	}

	if (motion.relord_time >= status.relord_time / 2 &&
		motion.relord_time <= status.relord_time) {
		tweek(motion.relord_time / status.relord_time, status.relord_motion, 0, motion.relord_motion);
	}
	if (motion.relord_time >= status.relord_time) {
		motion.relord = false;
		SE.find("end")->start();
		motion.relord_time = 0;
		status.bullets = status.max_bullets;
		motion.relord_motion = 0;
	}

}


void WeaponBase::update(const float& delta_time)
{
	if (drop == true) return;
	fire(delta_time);
	relordMotion(delta_time);
}
void WeaponBase::drawHaveWeapon() {
	if (drop == true) return;

	if (motion.scatter <= 0)
		motion.scatter = 0;

	motion.scatter -= 0.1f;
	ci::gl::pushModelView();
	ci::gl::multModelView(CAMERA.getMatrix());
	ci::Matrix44f matrix_t = ci::Matrix44f::createTranslation(ci::Vec3f(status.matrix_t.x, status.matrix_t.y, status.matrix_t.z + motion.relord_motion));
	ci::Matrix44f matrix_r = ci::Matrix44f::createRotation(ci::Vec3f(-motion.scatter + status.matrix_r.x, status.matrix_r.y + motion.relord_motion, -motion.scatter + motion.relord_motion + status.matrix_r.z));

	matrix = matrix_t*matrix_r;
	ci::gl::multModelView(matrix);
	material.apply();
	TEX.get(name).enableAndBind();
	glLoadMatrixf(matrix);
	ci::gl::scale(size);
	ci::gl::draw(mesh);
	TEX.get(name).disable();
	glLoadMatrixf(ci::Matrix44f::identity());
	ci::gl::popModelView();

}
void WeaponBase::drawDropWeapon() {
	if (!drop) return;

	rotate.y += 1.0f;
	ci::gl::pushModelView();
	material.apply();
	TEX.get(name).enableAndBind();
	ci::gl::translate(pos);
	ci::gl::rotate(ci::Vec3f(0.0f, rotate.y, 0.0f));
	ci::gl::scale(ci::Vec3f(0.01, 0.01, 0.01));
	ci::gl::draw(mesh);
	TEX.get(name).disable();
	ci::gl::popModelView();

	ci::gl::pushModelView();
	ci::gl::drawStrokedCube(pos, ci::Vec3i(4,4,4));
	ci::gl::popModelView();
}

void WeaponBase::draw()
{
	drawHaveWeapon();
	drawDropWeapon();
}
