#include "Camera.h"
#include "../../Utility/Input/Input.h"
MainCamera::MainCamera() : ObjectBase(ci::Vec3f(0,0,0), ci::Vec3f(0, 0, 0), ci::Vec3f(0, 0, 0))
{
	camera = ci::CameraPersp(1500, 1000,
		// 視野角
		60.0f,
		// near-z, far-z
		0.1f, 10000.0f);
	camera.setEyePoint(pos);
	camera.setCenterOfInterestPoint(ci::Vec3f(0, 0.0f, 1000.0f));
	scatter = 0;

	ci::gl::pushModelView();
	parent = ci::Matrix44f::identity();
	ci::Matrix44f parent_t = ci::Matrix44f::createTranslation(ci::Vec3f(0.0f, 0.0f, 0.0f));
	ci::Matrix44f parent_r = ci::Matrix44f::createRotation(ci::Vec3f(0, 0, 0));
	parent = parent_t*parent_r;
	ci::gl::popModelView();
	jump_flag = false;
}
MainCamera::MainCamera(const ci::Vec3f& _pos, const ci::Vec3f& _size, const ci::Vec3f& _rotate) : ObjectBase(_pos, _size,_rotate) {
	
	

}

void MainCamera::draw() {

	ci::gl::multModelView(GL_MODELVIEW);
	ci::gl::setMatrices(camera);

	ci::gl::enableDepthRead();
	ci::gl::enableDepthWrite();
	ci::gl::enable(GL_CULL_FACE);


}
void MainCamera::draw2d()
{
	ci::gl::setMatrices(camera_o);
	ci::gl::disableDepthRead();
	ci::gl::disableDepthWrite();
	ci::gl::disable(GL_CULL_FACE);
}
void MainCamera::move()
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
}
void MainCamera::jump()
{
	jump_flag = false;


	/*if (vec.y > 0.2f) {
		if (jump_flag == false) {
			if (ENV.pressKey(ci::app::KeyEvent::KEY_SPACE)) {
				vec.y = -0.2;
				jump_flag = true;
			}
		}
	}

	pos.y -= vec.y;
	if (vec.y < 0.2f) {
		vec.y += 0.015;
	}*/
}
void is_active(const int& hp,bool& arrive) {
	if (hp <= 0) {
		arrive = false;
	}
}

void weaponScatter(float& scatter,ci::Vec3f& insert_point, ci::Vec2f& camera_angle,
	
	ci::Ray& ray, ci::CameraPersp& camera,const ci::Vec3f& pos) {
	if (scatter <= 0) {
		scatter = 0;
	}
	scatter -= 0.4f;
	insert_point.x = 1 * sin(camera_angle.x) * 1 * cos(camera_angle.y);
	insert_point.z = 1 * cos(camera_angle.x) * 1 * cos(camera_angle.y);
	insert_point.y = sin(camera_angle.y);

	camera.setEyePoint(pos + ci::Vec3f(0, 0.5f, 0) - ci::Vec3f(scatter*sin(camera_angle.x), scatter, scatter*cos(camera_angle.x)));
	camera.setCenterOfInterestPoint(pos + insert_point + ci::Vec3f(0, 0.5f, 0) - ci::Vec3f(scatter*sin(camera_angle.x), scatter, scatter*cos(camera_angle.x)));
	ray.setOrigin(pos + ci::Vec3f(0, 0.5f, 0) - ci::Vec3f(scatter*sin(camera_angle.x), 0.0f, scatter*cos(camera_angle.x)));
	ray.setDirection(insert_point * (1000, 1000, 1000) + ci::Vec3f(0, 0.5f, 0) - ci::Vec3f(scatter*sin(camera_angle.x), 0.0f, scatter*cos(camera_angle.x)));
}

void MainCamera::update() {
	is_active(hp, arrive);
	weaponScatter(scatter, insert_point, camera_angle, ray,camera,pos);
	move();
	jump();
}

void MainCamera::setup()
{
	camera_o = ci::CameraOrtho(0, 1500,        // 画面左の座標、画面右の座標
		1000, 0,       // 画面下端の座標、画面上端の座標
		1, 10);                 // 画面手前の座標、画面奥の座標

	camera_o.setEyePoint(ci::Vec3f(0.0f, 0.0f, 0.0f));
	camera_o.setCenterOfInterestPoint(ci::Vec3f(0.0f, 0.0f, -1000.0f));
	ci::gl::enableAlphaBlending();
	hp = 100;
}

