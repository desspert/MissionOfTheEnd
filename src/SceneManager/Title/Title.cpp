#include "Title.h"
#include "../../Objects/Camera/Camera.h"
#include "../../dessUI/UIPlate/TitleUI/TitleUI.h"
#include "../../Utility/SoundManager.h"
#include "../../Utility/Input/Input.h"
void Title::setup()
{
	ui = std::make_shared<TitleUI>();
	ui->setup(dess::SceneName::TITLE);
	SE.registerFilePlayerNode("TitleBgm", "Sound/Music/haijin.mp3");
	SE.find("TitleBgm")->start();
	SE.find("TitleBgm")->setLoopEnabled(true);
}


void Title::update(const float& delta_time)
{
	ui->update(delta_time);
	
}

void Title::draw()
{
	ci::gl::clear(ci::ColorA8u(1, 1, 1, 1));
	CAMERA.draw2d();
	ui->draw();
	shift();
}

void Title::shift()
{
	if (ENV.pushKey(ci::app::KeyEvent::KEY_SPACE)) {
		SE.find("TitleBgm")->disable();
		SE.allStop();
		SE.allCrear();
		SCENE.shift(game::SceneName::GAMEMAIN);
	}
}

