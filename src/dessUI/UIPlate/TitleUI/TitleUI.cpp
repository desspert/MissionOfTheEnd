#include "TitleUI.h"
#include "../../../Utility/Input/Input.h"
#include "../../../SceneManager/SceneManager.h"
#include "../../../Utility/SoundManager.h"
void TitleUI::setup(const dess::SceneName & name)
{
	UIPlate::setup(name);
	ui_data["Mission"]->setActive(true);
	ui_data["Of"]->setActive(true);
	ui_data["TheEnd"]->setActive(true);
	ui_data["PushSpace"]->setActive(true);
}

void TitleUI::update(const float& delta_time)
{
	UIPlate::update(delta_time);
	
}

void TitleUI::draw()
{
	UIPlate::draw();
	if (ENV.pushKey(ci::app::KeyEvent::KEY_SPACE)) {
		SE.find("TitleBgm")->disable();
		SE.allStop();
		SE.allCrear();
		SCENE.shift(SceneName::GAMEMAIN);
	}
}