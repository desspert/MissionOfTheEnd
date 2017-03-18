#pragma once
#include "../DamageObjects.h"

class Player : public DamageObject
{
private:
	
public:
	Player(const ci::Vec3f & _pos,
		const ci::Vec3f & _size,
		const ci::Vec3f & _rotate,
		const std::string& _name,
		const std::string& _path);
	void setup() override;
	void move();
	void update() override;
	void draw() override;
	
};