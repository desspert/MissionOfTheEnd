#pragma once
#include "../SceneBase.h"
#include "../SceneManager.h"

class TitleUI;
class Title : public SceneBase
{
private:
	std::shared_ptr<TitleUI> ui;
	int count;
	bool start;
public:
	Title(){}
	void setup() override;
	void update(const float& delta_time) override;
	void draw() override;
	void shift();
};