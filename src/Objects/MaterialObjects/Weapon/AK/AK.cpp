#include "AK.h"
#include "cinder/ObjLoader.h"
#include "../../../../Utility/Texture.h"
#include "../../../../Utility/SoundManager.h"

AK::AK(const ci::Vec3f & _pos,
	const ci::Vec3f & _size, const ci::Vec3f & _angle,
	const std::string & _name, const std::string & _path)
	:WeaponBase(_pos, _size, _angle, _name, _path)
{
	TEX.set(_name, _path);
}

void AK::loading() {

	ci::ObjLoader loader = ci::ObjLoader(ci::app::loadAsset("Objects/Weapons/AK/Vz-58.obj"));
	SE.registerBufferPlayerNode(name, "Sound/SE/Weapons/AK/ak47-1.wav");
	SE.registerBufferPlayerNode("relord", "Sound/SE/Weapons/ak47_draw.wav");
	SE.registerBufferPlayerNode("end", "Sound/SE/Weapons/ak47_boltpull.WAV");
	loader.load(&mesh, boost::logic::indeterminate, boost::logic::indeterminate,
		false);

}

void AK::materialSetup() {

	material = ci::gl::Material(
		ci::ColorA(1, 1, 1, 1.0f),    // ����
		ci::ColorA(0.8f, 0.8f, 0.8f, 1.0f),    // �g�U��
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f),    // ���ʌ�
		80.0f,                             // ���ʔ���
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));   // ���Ȕ����F

}

void AK::statusInit() {

	status.rate = 8;
	status.attack_point = 30;
	status.scatter = 0.5f;
	status.bullets = 30;
	status.max_bullets = 30;
	status.relord_motion = 0.7f;
	status.matrix_t = ci::Vec3f(0.4f, -0.3f, -0.7f);
	status.matrix_r = ci::Vec3f(0, 2.9f*M_PI / 6, 0);
}

void AK::motionReset() {
	motion.rate = 0;
	motion.trigger = false;
	motion.relord = false;
	motion.scatter = 0;
	motion.relord_time = 0;
	motion.relord_motion = 0.0f;
	motion.rotation = 0.0f;
}
void AK::setup()
{
	loading();
	materialSetup();
	statusInit();
	motionReset();
	matrix = ci::Matrix44f::identity();
	drop = false;
	weapon_type = WeaponType::AK;
}

