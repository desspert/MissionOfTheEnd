#include "PK.h"
#include "cinder/ObjLoader.h"
#include "../../../../Utility/Texture.h"
#include "../../../../Utility/SoundManager.h"

PK::PK(const ci::Vec3f & _pos,
	const ci::Vec3f & _size, const ci::Vec3f & _angle,
	const std::string & _name, const std::string & _path)
	:WeaponBase(_pos, _size, _angle, _name, _path)
{
	TEX.set(_name, _path);
	ride_map = ci::Ray(_pos + ci::Vec3f(4, 4, 4), ci::Vec3f(0, -1000, 0));
}

void PK::loading() {

	ci::ObjLoader loader = ci::ObjLoader(ci::app::loadAsset("Objects/Weapons/PK/Pulemet.obj"));
	SE.registerBufferPlayerNode(name, "Sound/SE/Weapons/PK/m249-1.wav");
	SE.registerBufferPlayerNode("relord", "Sound/SE/Weapons/ak47_draw.wav");
	SE.registerBufferPlayerNode("end", "Sound/SE/Weapons/ak47_boltpull.WAV");
	loader.load(&mesh, boost::logic::indeterminate, boost::logic::indeterminate,
		false);

}

void PK::materialSetup() {

	material = ci::gl::Material(
		ci::ColorA(1, 1, 1, 1.0f),    // ä¬ã´åı
		ci::ColorA(0.8f, 0.8f, 0.8f, 1.0f),    // ägéUåı
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f),    // ãæñ åı
		80.0f,                             // ãæñ îΩéÀ
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));   // é©å»î≠åıêF

}

void PK::statusInit() {

	status.rate = 0.08f;
	status.attack_point = 40;
	status.scatter = 0.025f;
	status.bullets = 100;
	status.max_bullets = 100;
	status.relord_motion = 0.7f;
	status.relord_time = 2.0f;
	status.muzzle_pos = ci::Vec2f(700, 500);
	status.matrix_t = ci::Vec3f(0.21f, -0.6f, 0);
	status.matrix_r = ci::Vec3f((-12 * M_PI / 180) + 0.5f , 185 * M_PI / 180, (-25 * M_PI / 180) + 0.4f);
}

void PK::motionReset() {
	motion.rate = 0;
	motion.trigger = false;
	motion.relord = false;
	motion.scatter = 0;
	motion.relord_time = 0;
	motion.relord_motion = 0.0f;
	motion.rotation = 0.0f;
}
void PK::setup()
{
	ObjectBase::update();
	loading();
	materialSetup();
	statusInit();
	motionReset();
	matrix = ci::Matrix44f::identity();
	drop = true;
	weapon_type = WeaponType::PK;
}

void PK::drawDropWeapon()
{
	if (!drop) return;

	rotate.y += 1.0f;
	ci::gl::pushModelView();
	material.apply();
	TEX.get(name).enableAndBind();
	ci::gl::translate(pos - ci::Vec3f(0,2,0) );
	ci::gl::rotate(ci::Vec3f(0.0f, rotate.y, 0.0f));
	ci::gl::scale(ci::Vec3f(0.01, 0.01, 0.01));
	ci::gl::draw(mesh);
	TEX.get(name).disable();
	ci::gl::popModelView();

	ci::gl::pushModelView();
	ci::gl::drawStrokedCube(pos, ci::Vec3i(4, 4, 4));
	ci::gl::popModelView();
}

