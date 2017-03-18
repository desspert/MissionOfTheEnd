#pragma once
#include "cinder/app/AppNative.h"


//自作３次元ボックスのあたり判定
static bool collisionBoxToBox(ci::Vec3f box_pos1, ci::Vec3f box_size1, ci::Vec3f box_pos2, ci::Vec3f box_size2) {
	box_pos1 -= box_size1 / 2;
	box_pos2 -= box_size2 / 2;
	if (box_pos2.x < box_pos1.x + box_size1.x) {
		if (box_pos2.x + box_size2.x > box_pos1.x) {
			if (box_pos2.y < box_pos1.y + box_size1.y) {
				if (box_pos2.y + box_size2.y > box_pos1.y) {
					if (box_pos2.z < box_pos1.z + box_size1.z) {
						if (box_pos2.z + box_size2.z > box_pos1.z) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

static bool returnBoxToRayPoint(ci::Vec3f box_pos, ci::Vec3f box_size, ci::Vec3f ray_point) {
	box_pos -= box_size / 2;
	if (box_pos.x <= ray_point.x) {
		if (box_pos.x + box_size.x >= ray_point.x) {
			if (box_pos.y <= ray_point.y) {
				if (box_pos.y + box_size.y >= ray_point.y) {
					if (box_pos.z <= ray_point.z) {
						if (box_pos.z + box_size.z >= ray_point.z) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}
}

//自作３次元ボックスの物理判定
//エの字の判定を取っているので、
//一定以上の速度でなければ上下左右は大丈夫
//重ねるとたまにガバるけど９０％くらい大丈夫
//そして重さの根源
//box1は当たりに行くもの
//box2は当てられるもの
static ci::Vec3f returnBoxToBox(ci::Vec3f box_pos1, ci::Vec3f box_size1, ci::Vec3f box_pos2, ci::Vec3f box_size2) {
	if (collisionBoxToBox(box_pos1, box_size1, box_pos2, box_size2)) {
		box_pos1 -= box_size1 / 2;
		box_pos2 -= box_size2 / 2;

		if (box_pos2.y + (box_size2.y * 3) / 4 < box_pos1.y) {
			if (box_pos2.y + box_size2.y > box_pos1.y) {
				box_pos1 += box_size1 / 2;
				return ci::Vec3f(box_pos1.x, box_pos2.y + box_size2.y + box_size1.y / 2, box_pos1.z);
			}
		}



		if (box_pos2.y  < box_pos1.y + box_size1.y) {
			if (box_pos2.y + box_size2.y / 4 > box_pos1.y + box_size1.y) {
				box_pos1 += box_size1 / 2;
				return ci::Vec3f(box_pos1.x, box_pos2.y - box_size1.y / 2, box_pos1.z);
			}
		}

		if (box_pos2.x  < box_pos1.x + box_size1.x) {
			if (box_pos2.x + box_size2.x / 2 > box_pos1.x + box_size1.x) {
				box_pos1 += box_size1 / 2;
				return ci::Vec3f(box_pos2.x - box_size1.x / 2, box_pos1.y, box_pos1.z);
			}
		}
		
		

		if (box_pos2.x + box_size2.x / 2 < box_pos1.x) {
			if (box_pos2.x + box_size2.x > box_pos1.x) {
				box_pos1 += box_size1 / 2;
				return ci::Vec3f(box_pos2.x + box_size2.x + box_size1.x / 2, box_pos1.y, box_pos1.z);
			}
		}

		if (box_pos2.z  < box_pos1.z + box_size1.z) {
			if (box_pos2.z + box_size2.z / 2 > box_pos1.z + box_size1.z) {
				box_pos1 += box_size1 / 2;
				return ci::Vec3f(box_pos1.x, box_pos1.y, box_pos2.z - box_size1.z / 2);
			}
		}
		

		if (box_pos2.z + box_size2.z / 2 < box_pos1.z) {
			if (box_pos2.z + box_size2.z > box_pos1.z) {
				box_pos1 += box_size1 / 2;
				return ci::Vec3f(box_pos1.x, box_pos1.y, box_pos2.z + box_size2.z + box_size1.z / 2);
			}
		}
		box_pos1 += box_size1 / 2;
		box_pos2 += box_size2 / 2;
	}
	
	return box_pos1;
}
	
