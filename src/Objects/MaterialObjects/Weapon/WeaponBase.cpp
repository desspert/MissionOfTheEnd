#include "WeaponBase.h"
#include "../../../Utility/SoundManager.h"
#include "../../../Utility/Input/Input.h"
#include "../../Camera/Camera.h"
#include "../../../Utility/Easing/Easing.h"
#include "../../../Utility/Texture.h"
void WeaponBase::fire()
{
	motion.trigger = false;
	if (motion.relord == true) return;
	if (status.bullets <= 0) return;
	if (ENV.pressKey(ci::app::MouseEvent::LEFT_DOWN)) {
		motion.rate++;

		if (motion.rate == 1) {
			SE.find(name)->start();
			status.bullets--;
			CAMERA.cameraScatter(status.scatter);
			motion.scatter = status.scatter;
			motion.trigger = true;
		}

		if (motion.rate == status.rate) {
			motion.rate = 0;
			
		}
	}
	if (ENV.pullKey(ci::app::MouseEvent::LEFT_DOWN)) {
		motion.rate = 0;
	}


}

void WeaponBase::relordMotion()
{

	if (status.bullets == status.max_bullets) return;

	if (ENV.pushKey(ci::app::KeyEvent::KEY_r)) {
		motion.relord = true;
	}

	if (!motion.relord) return;

	motion.relord_time++;

	if (motion.relord_time == 1) {
		SE.find("relord")->start();
		c_Easing::apply(motion.relord_motion, status.relord_motion, EasingFunction::CubicIn, 30);
		c_Easing::apply(motion.relord_motion, 0.0f, EasingFunction::CubicIn, 30);
	}

	if (motion.relord_time == 30) {
		SE.find("end")->start();
	}

	if (motion.relord_time >= 60) {
		motion.relord = false;
		motion.relord_time = 0;
		status.bullets = status.max_bullets;
	}

}


void WeaponBase::update()
{
	if (drop == true) return;
	fire();
	relordMotion();
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
