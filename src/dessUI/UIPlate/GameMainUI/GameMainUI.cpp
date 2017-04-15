#include "GameMainUI.h"
#include "../../../Utility/SoundManager.h"
#include "../../../SceneManager/SceneManager.h"
#include "../../../Utility/Input/Input.h"
void GameMainUI::move()
{
	if (ENV.pressKey(ci::app::KeyEvent::KEY_w)) {
		ui_data["WB"]->setActive(true);
	}
	else {
		ui_data["WB"]->setActive(false);
	}
	if (ENV.pressKey(ci::app::KeyEvent::KEY_a)) {
		ui_data["AB"]->setActive(true);
	}
	else {
		ui_data["AB"]->setActive(false);
	}
	if (ENV.pressKey(ci::app::KeyEvent::KEY_s)) {
		ui_data["SB"]->setActive(true);
	}
	else {
		ui_data["SB"]->setActive(false);
	}
	if (ENV.pressKey(ci::app::KeyEvent::KEY_d)) {
		ui_data["DB"]->setActive(true);
	}
	else {
		ui_data["DB"]->setActive(false);
	}
	if (ENV.pressKey(ci::app::KeyEvent::KEY_r)) {
		ui_data["RB"]->setActive(true);
	}
	else {
		ui_data["RB"]->setActive(false);
	}
	if (ENV.pressKey(ci::app::KeyEvent::KEY_SPACE)) {
		ui_data["SpaceB"]->setActive(true);
	}
	else {
		ui_data["SpaceB"]->setActive(false);
	}
}

void GameMainUI::setup(const dess::SceneName & name)
{
	UIPlate::setup(name);
	kills = 0;
	boss_max_hp = 0;
	start_count = 0;
	SE.registerBufferPlayerNode("victory", "Sound/SE/vic.wav");
	SE.registerBufferPlayerNode("ready", "Sound/SE/gun-ready01.mp3");
	SE.registerBufferPlayerNode("start", "Sound/SE/gun-fire01.mp3");

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
	ui_data["R"]->setActive(true);
	ui_data["Space"]->setActive(true);
	ui_data["Message1Texture"]->setActive(true);
	ui_data["Message2Texture"]->setActive(true);
	ui_data["Message3Texture"]->setActive(true);
	ui_data["Message1"]->setActive(true);
	ui_data["Message1"]->fontSetText(u8"移動");
	ui_data["Message2"]->setActive(true);
	ui_data["Message2"]->fontSetText(u8"ジャンプ");
	ui_data["Message3"]->setActive(true);
	ui_data["Message3"]->fontSetText(u8"壁を壊して前へ進め！");
	ui_data["Message4"]->fontSetText(u8"武器を取得");
	ui_data["3"]->setActive(true);
}
void GameMainUI::bossSetup()
{
	ui_data["Message3"]->fontSetText(u8"ボスを倒せ！");
	ui_data["BossHP"]->setActive(true);
}
bool GameMainUI::start()
{
	start_count++;
	if (start_count == 60) {
		ui_data["3"]->setActive(false);
		ui_data["2"]->setActive(true);
		
	}
	if (start_count == 120) {
		ui_data["2"]->setActive(false);
		ui_data["1"]->setActive(true);
		
	}
	if (start_count == 180) {
		ui_data["1"]->setActive(false);
		ui_data["Go1"]->setActive(true);
		ui_data["Go2"]->setActive(true);
		ui_data["Go3"]->setActive(true);
		ui_data["Go1"]->setActive(false);
		ui_data["Go2"]->setActive(false);
		ui_data["Go3"]->setActive(false);
		SE.find("start")->start();
	}
	if (start_count >= 180) {
		return true;
	}
	
	return false;
}
void GameMainUI::update(const float& delta_time)
{
	UIPlate::update(delta_time);
	move();
}

void GameMainUI::draw()
{
	UIPlate::draw();
	ui_data["MuzzleFlash"]->setActive(false);
}


