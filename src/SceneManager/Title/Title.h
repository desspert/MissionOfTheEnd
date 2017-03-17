#pragma once
#include "../SceneBase.h"

#include "../SceneManager.h"
class Title : public SceneBase
{
private:
	

public:
	Title(){}
	void update(const float& delta_time) override;
	void draw() override;
	void setup() override;
};