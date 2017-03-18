#include "NormalEnemy.h"
#include "../../../../../Utility/Texture.h"

NormalEnemy::NormalEnemy(const ci::Vec3f & _pos,
	const ci::Vec3f & _size,
	const ci::Vec3f & _rotate,
	const std::string& _name,
	const std::string& _body_path,
	const std::string& _leg_name,
	const std::string& _leg_path,
	ci::TriMesh _body,
	ci::TriMesh _left_leg,
	ci::TriMesh _right_leg)
	: EnemyBase(_pos, _size, _rotate, _name, _body_path,
		_leg_name, _leg_path, _body, _left_leg, _right_leg)
{
	TEX.set(_name, _body_path);
	TEX.set(leg_name, _leg_path);
	
	material = ci::gl::Material(ci::ColorA(1, 1, 1, 1.0f),    
		ci::ColorA(0.8f, 0.8f, 0.8f, 1.0f),    
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f),    
		80.0f,                             
		ci::ColorA(0.0f, 0.0f, 0.0f, 1.0f));   

	hp = 100;

	motion.move_left_leg = 0;
	motion.move_right_leg = 0;
	motion.angle = 0.0f;
	motion.count = 0;
	motion.leg_inc = 0;
	motion.rotate_interval = 60;
	status.speed = 0.05f;
	status.attack = 10;
	status.scale = ci::Vec3f(0.06f, 0.06f, 0.06f);
}
