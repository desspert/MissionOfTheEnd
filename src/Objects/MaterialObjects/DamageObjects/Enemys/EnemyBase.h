#pragma once
#include "../DamageObjects.h"
#include "cinder/TriMesh.h"  

struct EnemyState {
	float speed;
	int attack;
	ci::Vec3f scale;
};

struct EnemyMotion {
	float angle;
	float leg_inc;
	float move_left_leg;
	float move_right_leg;
	int count;
	int rotate_interval;
};

class EnemyBase : public DamageObject
{
protected:
	ci::TriMesh body;
	ci::TriMesh left_leg;
	ci::TriMesh right_leg;

	std::string leg_name;

	EnemyState status;
	EnemyMotion motion;


	virtual void trackingToPlayer();
	virtual void walk();
	virtual void drawLeftLeg();
	virtual void drawRightLeg();
	virtual void drawBody();
public:
	EnemyBase(const ci::Vec3f & _pos,
		const ci::Vec3f & _size,
		const ci::Vec3f & _rotate,
		const std::string& _name,
		const std::string& _body_path,
		const std::string& _leg_name,
		const std::string& _leg_path,
		ci::TriMesh _body,
		ci::TriMesh _left_leg,
		ci::TriMesh _right_leg);

	const int& getAttack() {
		return status.attack;
	};
	void update() override;

	void draw() override;
};