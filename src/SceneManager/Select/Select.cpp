#include "Select.h"
#include "SelectProduction.cpp"
Select::Select() : _m(std::make_shared<_coroutine>(*this))
{
	camera_pos = ci::vec2(0);
	is_start = true;
	pause = false;
	gasya_production = false;
	ui.setPause(&pause);
	CAMERA.followingCamera(&camera_pos, ci::vec2(select_::WINDOW_WIDTH, select_::WINDOW_HEIGHT));
	SE.registerFilePlayerNode("SelectBGM", "Music/kikaikoujou.mp3");
	SE.registerBufferPlayerNode("Select", "SE/decide2.wav");
	SE.registerBufferPlayerNode("Back", "SE/highspeed-movement1.mp3");
	SE.registerBufferPlayerNode("GasyaSelect", "SE/decision4.mp3");
	TEX.set("Gasya", "Characters/kouhakuhikari.png");
	TEX.set("Tap", "UI/UITexture/Select/pipo-btleffect038.png");
	TEX.set("GasyaSpawn", "Characters/GasyaSpawn.png");
	TEX.set("GasyaEnd", "Characters/gasya_end.png");
}

void Select::setup()
{
	_m->setup();
	ui.setup(dess::SceneName::SELECT);
}

void Select::update(const float & delta_time)
{
	ANIMATION.update(delta_time);
	ui.update(delta_time);
	_m->update(delta_time);
}

void Select::draw()
{
	ci::gl::pushModelView();
	ci::gl::translate(ci::vec3(0, 0, CAMERA.getPos().z + 1500));
	ui.draw();
	ANIMATION.draw();
	ci::gl::popModelView();
	
}



void Select::mouseDown(const ci::app::MouseEvent & event)
{

	ui.mouseDown(event);
	
}

void Select::mouseDrag(const ci::app::MouseEvent & event)
{
	ui.mouseDrag(event);
}

void Select::mouseUp(const ci::app::MouseEvent & event)
{
	if (pause &&
		ui.isGasya()) {
		gasya_production = true;
		return;
	}
	if (!ui.isGasya()) {
		ui.mouseUp(event);
	}
}

void Select::touchesBegan(ci::app::TouchEvent event)
{
    
	ui.touchesBegan(event);
    
}

void Select::touchesMoved(ci::app::TouchEvent event)
{
	ui.touchesMoved(event);
}

void Select::touchesEnded(ci::app::TouchEvent event)
{
	ui.touchesEnded(event);
}
