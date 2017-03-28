#pragma once
#include <memory>
#include "cinder/app/AppNative.h"
#include "cinder/AxisAlignedBox.h"
enum ObjectType {
	WALL = 0,
	Enemy = 1,
	BREAKWALL = 2,
	BOSSCUBE = 3
};
class ObjectBase {
protected:
	ci::Ray ride_map;
	std::vector<ci::Vec3f> vertices;
	std::vector<uint32_t> indices;
	std::shared_ptr<ci::AxisAlignedBox3f> box;
	ci::Vec3f pos;
	ci::Vec3f size;
	ci::Vec3f rotate;
	bool arrive;
	int hp;
	ObjectType object_type;
public:
	ObjectBase(const ci::Vec3f& _pos, const ci::Vec3f& _size, const ci::Vec3f& _rotate) 
		: pos(_pos),size(_size), rotate(_rotate),ride_map(ci::Ray(_pos + ci::Vec3f(0, size.y, 0), ci::Vec3f(0, -1000, 0))) {
	}
	ci::Vec3f getPos() {
		return pos;
	}
	ci::Vec3f getSize() {
		return size;
	}
	ci::Vec3f getRotate() {
		return rotate;
	}
	void setPos(const ci::Vec3f& _pos) {
		pos = _pos;
	}
	void setSize(const ci::Vec3f& _size) {
		size = _size;
	}
	const int& getHp() {
		return hp;
	};
	
	bool getArrive() {
		return arrive;
	};
	const ObjectType& getObjectType() {
		return object_type;
	}
	std::shared_ptr<ci::AxisAlignedBox3f> getAABB() {
		return box;
	};
	const std::vector<ci::Vec3f>& getVertices(){
		return vertices;
	}
	const std::vector<uint32_t>& getIndices() {
		return indices;
	}

	const ci::Ray& getRideMapRay() {
		return ride_map;
	}

	virtual const int& getAttack() {
		return 0;
	};

	virtual bool isDead() { return false; }
	virtual void Damage(const int& damage) {}
	virtual void setup() {};
	virtual void draw() {};
	virtual void update() { ride_map.setOrigin(pos); };
	virtual void update(const float& delta_time) { };
};

