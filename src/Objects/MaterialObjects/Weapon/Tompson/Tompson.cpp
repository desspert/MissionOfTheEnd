#include "Tompson.h"
#include "cinder/ObjLoader.h"
#include "../../../../Utility/Texture.h"
#include "../../../../Utility/SoundManager.h"

Tompson::Tompson(const ci::Vec3f & _pos,
	const ci::Vec3f & _size, const ci::Vec3f & _angle,
	const std::string & _name, const std::string & _path)
	:WeaponBase(_pos, _size, _angle, _name, _path)
{
	TEX.set(_name, _path);
}

void Tompson::loading() {

	ci::ObjLoader loader = ci::ObjLoader(ci::app::loadAsset("Objects/Weapons/Tompson/gun.obj"));
	SE.registerBufferPlayerNode(name, "Sound/SE/Weapons/Tompson/fire-1.wav");
	SE.registerBufferPlayerNode("relord", "Sound/SE/Weapons/ak47_draw.wav");
	SE.registerBufferPlayerNode("end", "Sound/SE/Weapons/ak47_boltpull.WAV");
	loader.load(&mesh, boost::logic::indeterminate, boost::logic::indeterminate,
		false);

}

void Tompson::materialSetup() {

	material = ci::gl::Material(
		ci::ColorA(1, 1, 1, 1.0f),    // ä¬ã´åı
		ci::ColorA(0.8f, 0.8f, 0.8f, 1.0f),    // ägéUåı
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f),    // ãæñ åı
		80.0f,                             // ãæñ îΩéÀ
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));   // é©å»î≠åıêF

}

void Tompson::statusInit() {

	status.rate = 6;
	status.attack_point = 30;
	status.scatter = 0.5f;
	status.bullets = 50;
	status.max_bullets = 50;
	status.relord_motion = 0.7f;
	status.matrix_t = ci::Vec3f(0.2, -0.15,-0.6f);
	status.matrix_r = ci::Vec3f(0, 94 * M_PI / 180,0);
}

void Tompson::motionReset() {
	motion.rate = 0;
	motion.trigger = false;
	motion.relord = false;
	motion.scatter = 0;
	motion.relord_time = 0;
	motion.relord_motion = 0.0f;
	motion.rotation = 0.0f;
}
void Tompson::setup()
{
	loading();
	materialSetup();
	statusInit();
	motionReset();
	matrix = ci::Matrix44f::identity();
	drop = false;
	weapon_type = WeaponType::Tompson;
}

