#pragma once
#include "../UIPlate.h"

class GameMainUI : public UIPlate
{
private :
	int max_hp;
	int kills;
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

	void setup(const dess::SceneName& name) override;
	void update(const float& delta_time) override;
	void draw() override;

};