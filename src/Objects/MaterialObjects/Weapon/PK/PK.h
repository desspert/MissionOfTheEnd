#pragma once
#include "../WeaponBase.h"

class PK : public WeaponBase
{
public:

	PK(const ci::Vec3f& _pos, const ci::Vec3f& _size,
		const ci::Vec3f& _angle, const std::string& _name,
		const std::string& _path);
	void loading() override;
	void materialSetup() override;
	void statusInit() override;
	void motionReset() override;
	void setup() override;
};