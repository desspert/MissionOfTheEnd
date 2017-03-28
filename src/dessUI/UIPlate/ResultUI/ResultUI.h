#pragma once
#include "../UIPlate.h"

class ResultUI : public UIPlate
{
private:

public:
	void setup(const dess::SceneName& name) override;
	void update(const float& delta_time) override;
	void draw() override;
};