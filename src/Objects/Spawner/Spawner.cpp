#include "Spawner.h"
#include <random>
//スポーンする敵の番号（０～２）をランダムで返す
int  Spawner::getRandom()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> e_type(0, 2);
	int enemy_type = e_type(mt);
	
	return enemy_type;
}

//スポーン位置をランダムで返す
ci::Vec3f Spawner::getEnemyPos()
{
	float pos_x = pos.x - size.x / 2;
	float pos_z = pos.z - size.z / 2;
	
	float size_x = pos.x + size.x / 2;
	float size_z = pos.z + size.z / 2;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> mt_pos_z(pos_z, size_z);
	std::uniform_real_distribution<float> mt_pos_x(pos_x, size_x);
	
	
	float mt_x = mt_pos_x(mt);
	float mt_z = mt_pos_z(mt);

	ci::Vec3f ret_pos = ci::Vec3f(mt_x, pos.y, mt_z);

	return ret_pos;
}

void Spawner::update()
{
	ObjectBase::update();
	spawn = false;
	decrement--;
	if (decrement == 0) {
		spawn = true;
		decrement = spawn_interval;
	}
}
