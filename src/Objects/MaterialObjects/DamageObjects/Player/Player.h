#pragma once
#include "../DamageObjects.h"

class Player : public DamageObject
{
private:
	float damage_count;
	void jump();
	void move();
public:
	Player(const ci::Vec3f & _pos,
		const ci::Vec3f & _size,
		const ci::Vec3f & _rotate,
		const std::string& _name,
		const std::string& _path);

	const float& getColorR() {
		return color_r;
	}
	void Damage(const int& damage) override {
		if (damage_count < 0) {
			hp -= damage;
			ci::app::console() << hp << std::endl;
			color_r = 1.0f;
			damage_count = 1.0f;
		}
	}
	void setup() override;
	void update(const float& delta_time) override;
	void draw() override;
	
};