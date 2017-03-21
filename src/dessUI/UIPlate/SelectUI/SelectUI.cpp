#include "SelectUI.h"
#include"../../../SceneManager/SceneManager.h"
void SelectUI::setup(const dess::SceneName & name)
{
	UIPlate::setup(name);
	ui_data["BackBattle"]->setActive(true);
	ui_data["GasyaRoom"]->setActive(true);
	ui_data["Battle"]->setActive(true);
	ui_data["Gasya"]->setActive(true);
	ui_data["Status"]->setActive(true);
	ui_data["HaveCoin"]->setActive(true);
	ui_data["Coin"]->setActive(true);
	for (auto it = ui_scrolls_key.begin(); it != ui_scrolls_key.end(); it++) {
		ui_data[(*it)]->setActive(true);
	}
}

void SelectUI::update(const float& delta_time)
{
	
	{
	ci::TextLayout font_buf;
	font_buf.setColor(ci::ColorA(
		ui_data["HaveCoin"]->fontGetColorR(),
		ui_data["HaveCoin"]->fontGetColorG(),
		ui_data["HaveCoin"]->fontGetColorB(),
		ui_data["HaveCoin"]->fontGetColorA()));
	font_buf.setFont(TEX.getFont());
	font_buf.addLine(std::to_string(PLAYERDATA.getHaveCoins()));
	font["HaveCoin"] = font_buf;
	}
	{
		ci::TextLayout font_buf;
		font_buf.setColor(ci::ColorA(
			ui_data["GasyaHaveCoin"]->fontGetColorR(),
			ui_data["GasyaHaveCoin"]->fontGetColorG(),
			ui_data["GasyaHaveCoin"]->fontGetColorB(),
			ui_data["GasyaHaveCoin"]->fontGetColorA()));
		font_buf.setFont(TEX.getFont());
		font_buf.addLine(std::to_string(PLAYERDATA.getHaveCoins()) + "/5");
		font["GasyaHaveCoin"] = font_buf;
	}
	UIPlate::update(delta_time);
	for (auto it = ui_scrolls_key.begin(); it != ui_scrolls_key.end(); it++) {
		ui_data[(*it)]->update();
	}

}

void SelectUI::draw()
{
	scroll_pos.y *= 0.95f;

	if (ui_data["Solo"]->getActive() ||
		ui_data["Multi"]->getActive()) {
		scroll_pos = ci::vec2(0, 0);
	}
	if (ui_data[ui_scrolls_key.back()]->getPosY() + scroll_pos.y > 750 &&
		ui_data[ui_scrolls_key[0]]->getPosY() + scroll_pos.y < 150) {
		for (auto it = ui_scrolls_key.begin(); it != ui_scrolls_key.end(); it++) {
			ui_data[(*it)]->setPos(ui_data[(*it)]->getPosX() + scroll_pos.x,
				ui_data[(*it)]->getPosY() + scroll_pos.y);
		}
	}


	for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
		if (!ui_data[(*it)]->getActive()) continue;

		if (ui_data[(*it)]->getUIType() == UITYPE::NormalUI ||
			ui_data[(*it)]->getUIType() == UITYPE::CollisionUI ||
			ui_data[(*it)]->getUIType() == UITYPE::GaugeUI ||
			ui_data[(*it)]->getUIType() == UITYPE::AnimationUI
			) {
			ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());
			textures[(*it)]->bind();

			ci::Rectf drawRect(ci::vec2(
				ui_data[(*it)]->getPosX(),
				ui_data[(*it)]->getPosY()),
				ci::vec2(
					ui_data[(*it)]->getPosX() + ui_data[(*it)]->getSizeX(),
					ui_data[(*it)]->getPosY() + ui_data[(*it)]->getSizeY()));

			ci::gl::draw(textures[(*it)], drawRect);
			ci::gl::color(1, 1, 1, 1);
			textures[(*it)]->unbind();

			if (ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
				ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());
				gauge_texture[(*it)]->bind();

				ci::Rectf drawGauge(ci::vec2(
					ui_data[(*it)]->gaugeGetPosX(),
					ui_data[(*it)]->gaugeGetPosY()),
					ci::vec2(
						ui_data[(*it)]->gaugeGetPosX() + ui_data[(*it)]->gaugeGetSizeX(),
						ui_data[(*it)]->gaugeGetPosY() + ui_data[(*it)]->gaugeGetSizeY()));

				ci::gl::draw(gauge_texture[(*it)], drawGauge);
				gauge_texture[(*it)]->unbind();
				ci::gl::color(1, 1, 1, 1);
			}
		}
		else if (ui_data[(*it)]->getUIType() == UITYPE::ScrollUI) {
			ci::gl::pushModelView();
			ci::gl::translate(ci::vec2(ui_data[(*it)]->getPosX() + (ui_data[(*it)]->getSizeX() / 2), ui_data[(*it)]->getPosY() + (ui_data[(*it)]->getSizeY() / 2)));
			ci::gl::scale(ci::vec2(scroll_scales[(*it)], scroll_scales[(*it)]));
			ci::gl::translate(ci::vec2(-(ui_data[(*it)]->getSizeX() / 2), -(ui_data[(*it)]->getSizeY() / 2)));
			ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());
			textures[(*it)]->bind();
			ci::Rectf drawRect(ci::vec2(
				0,
				0),
				ci::vec2(
					ui_data[(*it)]->getSizeX(),
					ui_data[(*it)]->getSizeY()));

			ci::gl::draw(textures[(*it)], drawRect);
			ci::gl::color(1, 1, 1, 1);
			textures[(*it)]->unbind();

			ci::gl::translate(ui_data[(*it)]->fontGetPosX(), ui_data[(*it)]->fontGetPosY());
			ci::gl::translate(ci::vec2(-50, -50));
			ci::gl::scale(ci::vec2(ui_data[(*it)]->fontGetScale(), ui_data[(*it)]->fontGetScale()));
			ci::gl::color(
				ui_data[(*it)]->fontGetColorR(),
				ui_data[(*it)]->fontGetColorG(),
				ui_data[(*it)]->fontGetColorB(),
				ui_data[(*it)]->fontGetColorA());
			ci::gl::draw(ci::gl::Texture2d::create(font[(*it)].render(true)));

			ci::gl::color(ci::Color::white());
			ci::gl::popModelView();


		}
		else if (ui_data[(*it)]->getUIType() == UITYPE::FontUI ||
			ui_data[(*it)]->getUIType() == UITYPE::IncrementTimeUI ||
			ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {

			ci::gl::pushModelView();
			ci::gl::translate(ui_data[(*it)]->getPosX(), ui_data[(*it)]->getPosY());
			ci::gl::translate(ci::vec2(-50, -50));
			ci::gl::scale(ci::vec2(ui_data[(*it)]->fontGetScale(), ui_data[(*it)]->fontGetScale()));
			ci::gl::color(
				ui_data[(*it)]->fontGetColorR(),
				ui_data[(*it)]->fontGetColorG(),
				ui_data[(*it)]->fontGetColorB(),
				ui_data[(*it)]->fontGetColorA());
			ci::gl::draw(ci::gl::Texture2d::create(font[(*it)].render(true)));

			ci::gl::color(ci::Color::white());

			ci::gl::popModelView();
		}
	}
}

void SelectUI::mouseDown(ci::app::MouseEvent event)
{
	move_pos = event.getPos();
	ANIMATION.animationAdd<Tap>(event.getPos(), 100);
}

void SelectUI::mouseDrag(ci::app::MouseEvent event)
{
	scroll_pos.y += event.getPos().y - move_pos.y;
	scroll_pos.y *= 0.7f;

	move_pos = event.getPos();
}

void SelectUI::mouseUp(ci::app::MouseEvent event)
{
	if (**pause) return;
	if (!ui_data["Solo"]->getActive() ||
		!ui_data["Multi"]->getActive()) {
		int selected_map = 0;
		for (auto it = ui_scrolls_key.begin(); it != ui_scrolls_key.end(); it++) {
			selected_map++;
			if (ui_data[(*it)]->collisionToUI(des::Vec2f(event.getPos().x, event.getPos().y))) {
				if (c_Easing::isEnd(scroll_scales[(*it)])) {
					c_Easing::apply(scroll_scales[(*it)], 1.3f, EasingFunction::Linear, 1);
					c_Easing::apply(scroll_scales[(*it)], 1, EasingFunction::CircInOut, 20);
					SE.find("Select")->start();
					PLAYERDATA.selectMap(selected_map);
					ui_data["Fade"]->setActive(true);
					ui_data["Back"]->setActive(true);
					ui_data["Solo"]->setActive(true);
					ui_data["Multi"]->setActive(true);
				}
			}
		}
	}


	////オプション中
	//if (ui_data["Option"]->collisionToUI(des::Vec2f(event.getPos().x, event.getPos().y))) {
	//	sceneOption();
	//}
	//クエスト中
	if (ui_data["BackGasya"]->isEasingEnd()) {
		if (!ui_data["BackGasya"]->getActive()) {
			if (ui_data["Gasya"]->collisionToUI(des::Vec2f(event.getPos().x, event.getPos().y))) {
				sceneGasya();
			}
			if (ui_data["Back"]->collisionToUI(des::Vec2f(event.getPos().x, event.getPos().y))) {
				SE.find("Back")->start();
				ui_data["Fade"]->setActive(false);
				ui_data["Back"]->setActive(false);
				ui_data["Solo"]->setActive(false);
				ui_data["Multi"]->setActive(false);
			}
			if (ui_data["Multi"]->collisionToUI(des::Vec2f(event.getPos().x, event.getPos().y))) {

				SE.find("Select")->start();
				ui_data["Solo"]->setActive(false);


			}
			if (ui_data["Solo"]->collisionToUI(des::Vec2f(event.getPos().x, event.getPos().y))) {
				SE.find("Select")->start();
				is_end = true;
				return;
			}
		}
	}

	//ガシャ中
	if (ui_data["BackBattle"]->isEasingEnd()) {
		if (!ui_data["BackBattle"]->getActive()) {
			if (ui_data["Battle"]->collisionToUI(des::Vec2f(event.getPos().x, event.getPos().y))) {
				sceneBattle();
			}
			if (PLAYERDATA.getHaveCoins() >= 5) {
				if (ui_data["GasyaButton"]->collisionToUI(des::Vec2f(event.getPos().x, event.getPos().y))) {
					SE.find("GasyaSelect")->start();
					is_gasya = true;
					**pause = true;
				}
			}
		}
	}

}

void SelectUI::touchesBegan(ci::app::TouchEvent event)
{
	move_pos = event.getTouches()[0].getPos();
}

void SelectUI::touchesMoved(ci::app::TouchEvent event)
{
	scroll_pos.y += event.getTouches()[0].getPos().y - move_pos.y;
	scroll_pos.y *= 0.7f;
}

void SelectUI::touchesEnded(ci::app::TouchEvent event)
{
	if (**pause) return;
	ci::vec2 touch_pos;
	ci::vec2 window_size = ci::app::getWindowSize();
	touch_pos.x = event.getTouches()[0].getX() * (select_::WINDOW_WIDTH / window_size.x);
	touch_pos.y = event.getTouches()[0].getY() * (select_::WINDOW_HEIGHT / window_size.y);

	ci::app::console() << window_size << std::endl;
	for (auto it = ui_scrolls_key.begin(); it != ui_scrolls_key.end(); it++) {
		if (ui_data[(*it)]->collisionToUI(des::Vec2f(touch_pos.x, touch_pos.y))) {
			SE.find("Select")->start();
		}
	}
	if (ui_data["Option"]->collisionToUI(des::Vec2f(touch_pos.x, touch_pos.y))) {
		sceneOption();
	}

	if (!ui_data["BackGasya"]->getActive()) {
		if (ui_data["Gasya"]->collisionToUI(des::Vec2f(touch_pos.x, touch_pos.y))) {
			sceneGasya();
		}
		if (ui_data["Multi"]->collisionToUI(des::Vec2f(touch_pos.x, touch_pos.y))) {
			SE.find("Select")->start();
			ui_data["Solo"]->setActive(false);

			for (auto it = ui_scrolls_key.begin(); it != ui_scrolls_key.end(); it++) {
				ui_data[(*it)]->setActive(true);
			}
		}
		if (ui_data["Solo"]->collisionToUI(des::Vec2f(touch_pos.x, touch_pos.y))) {
			SE.find("Select")->start();
			is_end = true;
			return;
		}
	}


	if (!ui_data["BackBattle"]->getActive()) {
		if (ui_data["Battle"]->collisionToUI(des::Vec2f(touch_pos.x, touch_pos.y))) {
			sceneBattle();
		}
		if (ui_data["GasyaButton"]->collisionToUI(des::Vec2f(touch_pos.x, touch_pos.y))) {
			SE.find("Select")->start();
			is_gasya = true;
			**pause = true;
		}
	}
}



void SelectUI::sceneBattle()
{
	for (auto it = ui_scrolls_key.begin(); it != ui_scrolls_key.end(); it++) {
		ui_data[(*it)]->setActive(true);
	}
	ui_data["GasyaCoin"]->setActive(false);
	ui_data["GasyaHaveCoin"]->setActive(false);
	ui_data["BackGasya"]->setActive(false);
	ui_data["GasyaButton"]->setActive(false);
	ui_data["BackGasya"]->setActive(false);
	ui_data["BackBattle"]->setActive(true);
	SE.find("Select")->start();
}

void SelectUI::sceneGasya()
{
	ui_data["GasyaButton"]->setActive(true);
	ui_data["GasyaCoin"]->setActive(true);
	ui_data["GasyaHaveCoin"]->setActive(true);
	ui_data["BackGasya"]->setActive(true);
	ui_data["BackBattle"]->setActive(false);
	ui_data["Back"]->setActive(false);
	ui_data["Solo"]->setActive(false);
	ui_data["Multi"]->setActive(false);
	ui_data["Fade"]->setActive(false);
	for (auto it = ui_scrolls_key.begin(); it != ui_scrolls_key.end(); it++) {
		ui_data[(*it)]->setActive(false);
	}
	SE.find("Select")->start();
}

void SelectUI::sceneOption()
{
	//ui_data["Back"]->setActive(false);
	//ui_data["GasyaButton"]->setActive(false);
	//ui_data["BackGasya"]->setActive(false);
	//ui_data["BackBattle"]->setActive(false);
	//ui_data["Solo"]->setActive(false);
	//ui_data["Multi"]->setActive(false);
	//ui_data["GasyaCoin"]->setActive(false);
	//ui_data["GasyaHaveCoin"]->setActive(false);
	//for (auto it = ui_scrolls_key.begin(); it != ui_scrolls_key.end(); it++) {
	//	ui_data[(*it)]->setActive(false);
	//}
	//SE.find("Select")->start();
}

void SelectUI::multi()
{
}

void SelectUI::solo()
{
}

