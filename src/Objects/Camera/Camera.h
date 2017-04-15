#pragma once
#include "../ObjectBase.h"
#include "cinder/Camera.h"

namespace dess {
#define M_PI 3.14159265359
}
#define CAMERA MainCamera::get()


class MainCamera : public ObjectBase
{
private:
	ci::CameraPersp camera;
	ci::CameraOrtho camera_o;
	ci::Ray ray;
	ci::Vec2f camera_angle;
	ci::Vec3f insert_point;
	
	int code;
	ci::Matrix44f parent;
	ci::Matrix44f parent_t;
	ci::Matrix44f parent_r;
	float scatter;
	int walk;
	ci::Vec3f vec;
	float shake_range;
	float shake_seconds;

public:
	MainCamera();
	MainCamera(const ci::Vec3f& _pos, const ci::Vec3f& _size, const ci::Vec3f& _rotate);
	~MainCamera(){}
	void draw();
	void draw2d();
	void init();
	void update();
	void setup();
	void incliment_camera_angle(ci::Vec2f mouse_vec)
	{
		camera_angle -= mouse_vec * 0.005;
		camera_angle.y = std::min(float(M_PI / 2) - 0.01f,
			std::max(camera_angle.y, -float(M_PI / 2) + 0.01f));
		camera_angle.x = std::fmod(camera_angle.x, M_PI * 2.0);

	}
	void cameraScatter(float sc) {
		scatter += sc;
	}
	void shakeCamera(const float& scatter,const float& seconds);
	void shake(const float& delta_time);
	ci::Matrix44f getMatrix() {
		return parent;
	}

	ci::Ray& getRay() {
		return ray;
	}
	const ci::Vec2f& getCameraAngle() {
		return camera_angle;
	};
	const ci::Vec3f& getInsertPoint() {
		return insert_point;
	};
	
	static MainCamera& get() {
		static MainCamera cam;
		return cam;
	}
};

