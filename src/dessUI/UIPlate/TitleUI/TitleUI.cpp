#include "TitleUI.h"
#include "../../../Utility/Input/Input.h"
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
	
}