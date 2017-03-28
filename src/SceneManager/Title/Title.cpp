#include "Title.h"
#include "../../Objects/Camera/Camera.h"
#include "../../dessUI/UIPlate/TitleUI/TitleUI.h"
#include "../../Utility/SoundManager.h"
#include "../../Utility/Input/Input.h"
void Title::setup()
{
	count = 0;
	start = false;
	ui = std::make_shared<TitleUI>();
	ui->setup(dess::SceneName::TITLE);
	SE.registerFilePlayerNode("TitleBgm", "Sound/Music/haijin.mp3");
	SE.registerBufferPlayerNode("boss_effect", "Sound/SE/Boss/sword-clash1.mp3");
	SE.registerBufferPlayerNode("break", "Sound/SE/glass-break1.mp3");
	SE.registerBufferPlayerNode("select", "Sound/SE/button02b.mp3");
}


void Title::update(const float& delta_time)
{
	ui->update(delta_time);
	count++;
	if (count == 1) {
		ui->ui_data["Mission"]->setActive(true);
		ui->ui_data["Flash"]->setActive(true);
		ui->ui_data["Flash"]->setActive(false);
		SE.find("boss_effect")->start();
	}
	if (count == 60) {
		ui->ui_data["Of"]->setActive(true);
		ui->ui_data["Flash"]->setActive(true);
		ui->ui_data["Flash"]->setActive(false);
		SE.find("boss_effect")->start();
	}
	if (count == 150) {
		ui->ui_data["Of"]->setActive(true);
		ui->ui_data["TheEnd"]->setActive(true);
		ui->ui_data["Flash"]->setActive(true);
		ui->ui_data["Flash"]->setActive(false);
		ui->ui_data["PushSpace"]->setActive(true);
		SE.find("TitleBgm")->start();
		SE.find("TitleBgm")->setLoopEnabled(true);
		SE.find("break")->start();
	}

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
	if (count < 120) return;
	if (ENV.pushKey(ci::app::KeyEvent::KEY_SPACE)) {
		start = true;
		SE.find("select")->start();
		ui->ui_data["PushSpace"]->setActive(false);
		ui->ui_data["Fade"]->setActive(true);
	}
	if (start == true) {
		if (!ui->ui_data["PushSpace"]->getActive()) {
			SE.find("TitleBgm")->disable();
			SE.allStop();
			SE.allCrear();
			SCENE.shift(game::SceneName::GAMEMAIN);
		}
	}
}

