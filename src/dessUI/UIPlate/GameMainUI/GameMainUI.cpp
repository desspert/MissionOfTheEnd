#include "GameMainUI.h"

void GameMainUI::setup(const dess::SceneName & name)
{
	UIPlate::setup(name);
	kills = 0;
	ui_data["CrossHair"]->setActive(true);
	ui_data["BulletsUI"]->setActive(true);
	ui_data["KillsUI"]->setActive(true);
	ui_data["HPUI"]->setActive(true);
	ui_data["Kills"]->setActive(true);
	ui_data["HP"]->setActive(true);
	ui_data["Bullets"]->setActive(true);
	ui_data["BulletsTexture"]->setActive(true);
}

void GameMainUI::update(const float& delta_time)
{
	UIPlate::update(delta_time);
}

void GameMainUI::draw()
{
	UIPlate::draw();
	ui_data["MuzzleFlash"]->setActive(false);
}


