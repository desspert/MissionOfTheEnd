#pragma once
#include "../UIPlate.h"

class GameMainUI : public UIPlate
{
private :
	int kills;
	int boss_max_hp;
	int start_count;
public:
	
	void setHP(const int& hp) {
		ui_data["HP"]->fontSetText("HP" + std::to_string(hp));
	}
	void setBullets(const int& bullets) {
		ui_data["Bullets"]->fontSetText(std::to_string(bullets));
	}
	void addKills() {
		this->kills++;
		ui_data["Kills"]->fontSetText(std::to_string(kills) + "KILL");
	}
	void muzzleFlash(const ci::Vec2f& muzzle_pos,const bool& trigger) {
		ui_data["MuzzleFlash"]->setPos(muzzle_pos.x, muzzle_pos.y);
		ui_data["MuzzleFlash"]->setActive(trigger);
	}
	void getWeapon(const bool& collision) {
		ui_data["G"]->setActive(collision);
		ui_data["Message4Texture"]->setActive(collision);
		ui_data["Message4"]->setActive(collision);
	}
	void setGoal() {
		ui_data["Clear"]->setActive(true);
	}
	void setBossMaxHP(const int& boss_hp) {
		boss_max_hp = boss_hp;
	}
	void setBossHP(const int& boss_hp) {
		ui_data["BossHP"]->gaugeChangeX(static_cast<float>(boss_hp), boss_max_hp);
	}
	void move();
	void setup(const dess::SceneName& name) override;
	void bossSetup();
	bool start();
	void update(const float& delta_time) override;
	void draw() override;

};