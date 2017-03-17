#pragma once
#include "../../../ObjectBase.h"

class Player : public ObjectBase
{
private:
	
public:
	Player(const ci::Vec3f& _pos, const ci::Vec3f& _size,
		const ci::Vec3f& _rotate);
	void setup() override;
	void move();
	void update() override;
	void draw() override;
	
};