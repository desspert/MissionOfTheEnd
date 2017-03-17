#pragma once
#include <memory>
#include "cinder/app/AppNative.h"
#include "cinder/AxisAlignedBox.h"

class ObjectBase {
public:
	ObjectBase(const ci::Vec3f& _pos, const ci::Vec3f& _size, const ci::Vec3f& _rotate) 
		: pos(_pos),size(_size), rotate(_rotate) {
	}
	ci::Vec3f getPos() {
		return pos;
	}
	ci::Vec3f getSize() {
		return size;
	}
	void setPos(const ci::Vec3f& _pos) {
		pos = _pos;
	}
	void setSize(const ci::Vec3f& _size) {
		size = _size;
	}
	int getHp() {
		return hp;
	};
	bool getArrive() {
		return arrive;
	};
	std::shared_ptr<ci::AxisAlignedBox3f> getAABB() {
		return box;
	};
	const std::vector<ci::Vec3f>& getVertices(){
		return vertices;
	}
	const std::vector<uint32_t>& getIndices() {
		return indices;
	}

	std::shared_ptr<ci::Ray> getRideMapRay() {
		return ride_map;
	}

	virtual void setup() {};
	virtual void draw() {};
	virtual void update() {};
protected:
	std::shared_ptr<ci::Ray> ride_map;
	std::vector<ci::Vec3f> vertices;
	std::vector<uint32_t> indices;
	std::shared_ptr<ci::AxisAlignedBox3f> box;
	ci::Vec3f pos;
	ci::Vec3f size;
	ci::Vec3f rotate;
	bool arrive;
	int type;
	int hp;
};

