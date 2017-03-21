#pragma once
#include "../UIPlate.h"

class TitleUI : public UIPlate
{
public:
	void setup(const dess::SceneName& name) override;
	void update(const float& delta_time) override;
	void draw() override;
	
};