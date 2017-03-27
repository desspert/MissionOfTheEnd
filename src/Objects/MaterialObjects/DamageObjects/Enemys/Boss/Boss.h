#pragma once
#include "../EnemyBase.h"

class Boss : public EnemyBase
{
private:
	ci::Vec3f attack_pos;
	ci::Vec3f attack_size;
	int enemy_behavior_state;
	int behavior_count;
	int jump_count;

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
	ci::Vec3f getAttackPos() {
		return attack_pos;
	}
	ci::Vec3f getAttackSize() {
		return attack_size;
	}

};