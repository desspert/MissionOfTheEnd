#include "Deagle.h"
#include "cinder/ObjLoader.h"
#include "../../../../Utility/Texture.h"
#include "../../../../Utility/SoundManager.h"
#include "../../../../Utility/Input/Input.h"
#include "../../../Camera/Camera.h"
Deagle::Deagle(const ci::Vec3f & _pos,
	const ci::Vec3f & _size, const ci::Vec3f & _angle,
	const std::string & _name, const std::string & _path)
	:WeaponBase(_pos, _size, _angle, _name, _path)
{
	TEX.set(_name, _path);
}

void Deagle::loading() {

	ci::ObjLoader loader = ci::ObjLoader(ci::app::loadAsset("Objects/Weapons/Deagle/deagle.obj"));
	SE.registerBufferPlayerNode(name, "Sound/SE/Weapons/Deagle/deagle-1.wav");
	SE.registerBufferPlayerNode("relord", "Sound/SE/Weapons/ak47_draw.wav");
	SE.registerBufferPlayerNode("end", "Sound/SE/Weapons/ak47_boltpull.WAV");
	loader.load(&mesh, boost::logic::indeterminate, boost::logic::indeterminate,
		false);

}

void Deagle::materialSetup() {

	material = ci::gl::Material(ci::ColorA(1, 1, 1, 1.0f),    // ŠÂ‹«Œõ‚ª“–‚½‚Á‚½‚ÌF
		ci::ColorA(0.5f, 0.5f, 0.5f, 1.0f),    // ŠgUŒõ‚ª“–‚½‚Á‚½‚ÌF
		ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f),    // ‹¾–ÊŒõ‚ª“–‚½‚Á‚½‚ÌF
		80.0f,                             // ‹¾–Ê”½Ë‚Ì‰s‚³(’l‚ª‘å‚«‚¢‚Ù‚Ç‰s‚­‚È‚é)
		ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f));   // ©ŒÈ”­ŒõF

}

void Deagle::statusInit() {

	status.rate = 10;
	status.attack_point = 50;
	status.scatter = 0.5f;
	status.bullets = 7;
	status.max_bullets = 7;
	status.relord_motion = 0.7f;
	status.matrix_t = ci::Vec3f(0.060f, -0.05f, -0.10f);
	status.matrix_r = ci::Vec3f(180 * M_PI / 180 , 180 * M_PI / 180, 0);
}

void Deagle::motionReset() {
	motion.rate = 0;
	motion.trigger = false;
	motion.relord = false;
	motion.scatter = 0;
	motion.relord_time = 0;
	motion.relord_motion = 0.0f;
	motion.rotation = 0.0f;
}
void Deagle::setup()
{
	loading();
	materialSetup();
	statusInit();
	motionReset();
	matrix = ci::Matrix44f::identity();
	drop = false;
	weapon_type = WeaponType::Deagle;
}

void Deagle::fire()
{
	if (motion.relord == true) return;
	if (status.bullets <= 0) return;
	if (ENV.pushKey(ci::app::MouseEvent::LEFT_DOWN)) {
		motion.trigger = true;
	}

	if (motion.trigger == true) {
		motion.rate++;
		if (motion.rate == 1) {
			SE.find(name)->start();
			status.bullets--;
			CAMERA.cameraScatter(status.scatter);
			motion.scatter = 0.6f;
		}
		if (motion.rate == status.rate) {
			motion.rate = 0;
			motion.trigger = false;
		}
	}
}

