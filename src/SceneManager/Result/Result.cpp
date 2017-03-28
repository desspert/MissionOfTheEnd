#include "Result.h"
#include "../../Utility/SoundManager.h"
#include "../../Utility/Input/Input.h"
#include "../../dessUI/UIPlate/ResultUI/ResultUI.h"
void Result::setup()
{
	ui = std::make_shared<ResultUI>();
	ui->setup(dess::SceneName::RESULT);
	if (result == true) {
		ui->ui_data["Win"]->setActive(true);
		SE.registerBufferPlayerNode("win", "Sound/SE/jingle1.mp3");
		SE.find("win")->start();
	}
	else {
		ui->ui_data["Lose"]->setActive(true);
		SE.registerBufferPlayerNode("lose", "Sound/SE/lose.mp3");
		SE.find("lose")->start();
	}
	ui->ui_data["PushSpace"]->setActive(true);
	ui->ui_data["Fade"]->setActive(true);
}

void Result::update(const float & delta_time)
{
	ui->update(delta_time);
	if (ENV.pushKey(ci::app::KeyEvent::KEY_SPACE)) {
		ui->ui_data["Fade"]->setActive(false);
	}
	if (!ui->ui_data["Fade"]->getActive()) {
		SE.allStop();
		SE.allCrear();
		SCENE.shift(game::SceneName::TITLE);
	}
}

void Result::draw()
{
	ui->draw();
}
