#pragma once
#include "../DamageObjects.h"

class Player : public DamageObject
{
private:
	float damage_count;
	int walk_count;
	void jump();
	void move();
	void walk();
public:
	Player(const ci::Vec3f & _pos,
		const ci::Vec3f & _size,
		const ci::Vec3f & _rotate,
		const std::string& _name,
		const std::string& _path);

	const float& getColorR() {
		if (hp < 0) {
			return 1.0f;
		}
		return color_r;
	}
	void addHp() {
		hp++;
	}
	void Damage(const int& damage) override;
	void setup() override;
	void update(const float& delta_time) override;
	void draw() override;
	bool isDead() override;
};