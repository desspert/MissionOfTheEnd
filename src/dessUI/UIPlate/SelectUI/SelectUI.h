#pragma once
#include "../UIPlate.h"
#include "../../../ProductionCamera/ProductionCamera.h"
#include "../../../SoundManager.h"
#include "../../../Animation/Animation.h"
#include "../../../Animation/Production/Gasya/Gasya.h"
#include "../../../Animation/Production/Tap/Tap.h"
class SelectUI : public UIPlate
{ 
private:
	ci::vec2 scroll_pos;
	ci::vec2 move_pos;
	ci::vec2 buf_pos;
	ci::vec2 up_pos;
	bool is_end;
	bool is_gasya;
	std::shared_ptr<bool*> pause;
	
public:
	SelectUI(){
		is_end = false;
		is_gasya = false;
		scroll_pos = ci::vec2(0);
		move_pos = ci::vec2(0);
		up_pos = ci::vec2(0);
	}

	bool isEnd() {
		return is_end;
	}
	bool& isGasya() {
		return is_gasya;
	}

	void setPause(bool* pause) {
		this->pause = std::make_shared<bool*>(pause);
	}

	void setup(const dess::SceneName& name) override;
	void update(const float& delta_time) override;
	void draw() override;
	void mouseDown(ci::app::MouseEvent event);
	void mouseDrag(ci::app::MouseEvent event);
	void mouseUp(ci::app::MouseEvent event);
	void touchesBegan(ci::app::TouchEvent event);
	void touchesMoved(ci::app::TouchEvent event);
	void touchesEnded(ci::app::TouchEvent event);

	void selectGasya();
	void saveGasya();
	void sceneBattle();
	void sceneGasya();
	void sceneOption();
	void multi();
	void solo();
};
