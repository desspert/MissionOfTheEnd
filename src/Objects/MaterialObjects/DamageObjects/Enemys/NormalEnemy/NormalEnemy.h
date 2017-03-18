#pragma once
#include "../EnemyBase.h"

class NormalEnemy : public EnemyBase
{
public:
	NormalEnemy(const ci::Vec3f & _pos,
		const ci::Vec3f & _size,
		const ci::Vec3f & _rotate,
		const std::string& _name,
		const std::string& _body_path,
		const std::string& _leg_name,
		const std::string& _leg_path,
		ci::TriMesh _body,
		ci::TriMesh _left_leg,
		ci::TriMesh _right_leg);
};