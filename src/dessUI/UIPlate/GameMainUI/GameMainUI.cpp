#include "GameMainUI.h"
#include "../../../Utility/SoundManager.h"
#include "../../../SceneManager/SceneManager.h"

void GameMainUI::setup(const dess::SceneName & name)
{
	UIPlate::setup(name);
	kills = 0;
	boss_max_hp = 0;
	SE.registerBufferPlayerNode("victory", "Sound/SE/vic.wav");


	ui_data["CrossHair"]->setActive(true);
	ui_data["BulletsUI"]->setActive(true);
	ui_data["KillsUI"]->setActive(true);
	ui_data["HPUI"]->setActive(true);
	ui_data["Kills"]->setActive(true);
	ui_data["HP"]->setActive(true);
	ui_data["Bullets"]->setActive(true);
	ui_data["BulletsTexture"]->setActive(true);
	ui_data["W"]->setActive(true);
	ui_data["A"]->setActive(true);
	ui_data["S"]->setActive(true);
	ui_data["D"]->setActive(true);
	ui_data["Space"]->setActive(true);
	ui_data["Message1"]->setActive(true);
	ui_data["Message1"]->fontSetText(u8"移動");
	ui_data["Message2"]->setActive(true);
	ui_data["Message2"]->fontSetText(u8"ジャンプ");
	ui_data["Message3"]->setActive(true);
	ui_data["Message3"]->fontSetText(u8"壁を壊して前へ進め！");
}
void GameMainUI::bossSetup()
{
	ui_data["Message3"]->fontSetText(u8"ボスを倒せ！");
	ui_data["Clear"]->setActive(false);
	ui_data["BossHP"]->setActive(true);
}
void GameMainUI::goal()
{
	
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


