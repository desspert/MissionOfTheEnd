#pragma once
#include "../EnemyBase.h"

class Boss : public EnemyBase
{
private:
	
	int enemy_behavior_state;
	int behavior_count;
	int jump_count;
	int dash_count;
	float dash_motion_color;

	void trackingToPlayer();
	void jump();
	void dash();

	void selectBehavior();
	void behavior();
	void drawLeftLeg();
	void drawRightLeg();
	void drawBody();
public:
	Boss(const ci::Vec3f & _pos,
		const ci::Vec3f & _size,
		const ci::Vec3f & _rotate,
		const std::string& _name,
		const std::string& _body_path,
		const std::string& _leg_name,
		const std::string& _leg_path,
		ci::TriMesh _body,
		ci::TriMesh _left_leg,
		ci::TriMesh _right_leg);
	void update() override;
	void draw() override;
	

};