#pragma once
#include "../ObjectBase.h"

class Spawner : public ObjectBase
{
private:
	int spawn_interval;
	int rotate_interval;
	float speed;
	bool spawn;
	int decrement;
public:
	Spawner(const ci::Vec3f& _pos, const ci::Vec3f& _size,
		const ci::Vec3f& _rotate,int _spawn_interval, 
		int _rotate_interval, float _speed) 
		: ObjectBase(_pos, _size,_rotate)
	{
		spawn_interval = _spawn_interval;
		rotate_interval = _rotate_interval;
		speed = _speed;
		decrement = _spawn_interval;
	}
	const bool& isSpawn() {
		return spawn;
	}
	
	const int& getRotate() {
		return rotate_interval;
	}
	const float& getSpeed() {
		return speed;
	}

	int getRandom();

	const ci::Vec3f& getEnemyPos();

	void update() override;
};