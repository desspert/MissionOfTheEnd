#include "UIPlate.h"

void setData(std::unordered_map<std::string, ci::gl::Texture>& mTexture, const std::vector<std::string>& ui_objects,
	std::unordered_map<std::string, std::shared_ptr<UIBase>>& ui_data, std::unordered_map<std::string, ci::Font>& font,
	std::unordered_map<std::string, ci::gl::Texture>& gauge_texture) {

	for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {

		if (ui_data[(*it)]->getUIType() == UITYPE::NormalUI ||
			ui_data[(*it)]->getUIType() == UITYPE::CollisionUI ||
			ui_data[(*it)]->getUIType() == UITYPE::GaugeUI ||
			ui_data[(*it)]->getUIType() == UITYPE::AnimationUI ||
			ui_data[(*it)]->getUIType() == UITYPE::ScrollUI) {
			//テクスチャのパスをセット
			mTexture[(*it)] = ci::loadImage(ci::app::loadAsset(ui_data[(*it)]->getTexturePath()));
			if (ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
				auto img = ci::loadImage(ci::app::loadAsset(ui_data[(*it)]->gaugeGetTexturePath()));
				gauge_texture[(*it)] = ci::loadImage(ci::app::loadAsset(ui_data[(*it)]->gaugeGetTexturePath()));
			}

		}else if (ui_data[(*it)]->getUIType() == UITYPE::FontUI ||
			ui_data[(*it)]->getUIType() == UITYPE::IncrementTimeUI ||
			ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {
			if (ui_data[(*it)]->getUIType() == UITYPE::FontUI ||
				ui_data[(*it)]->getUIType() == UITYPE::IncrementTimeUI ||
				ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {
				font[(*it)] = ci::Font(ci::app::getAssetPath(ui_data[(*it)]->fontGetPath()).string(), ui_data[(*it)]->fontGetSize());
				continue;
			}
		}

	}
}

void UIPlate::setup(const dess::SceneName& name)
{

	JsonInit(name);
	setData(textures, ui_objects, ui_data, font, gauge_texture);
}

void UIPlate::update(const float& delta_time)
{
	for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
		ui_data[*it]->update();
	}

}

void UIPlate::draw()
{
	ci::gl::pushModelView();
	ci::gl::translate(0.0f, 0.0f, -3.0f);
	for (auto it = ui_objects.begin(); it != ui_objects.end(); it++) {
		if (!ui_data[(*it)]->getActive()) continue;

		if (ui_data[(*it)]->getUIType() == UITYPE::NormalUI ||
			ui_data[(*it)]->getUIType() == UITYPE::CollisionUI ||
			ui_data[(*it)]->getUIType() == UITYPE::GaugeUI ||
			ui_data[(*it)]->getUIType() == UITYPE::AnimationUI
			) {
			ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());
			textures[(*it)].enableAndBind();
			
			ci::gl::drawSolidRect(
				ci::Rectf(ci::Vec2f(
					ui_data[(*it)]->getPosX(),
					ui_data[(*it)]->getPosY()),
					ci::Vec2f(
						ui_data[(*it)]->getPosX() + ui_data[(*it)]->getSizeX(),
						ui_data[(*it)]->getPosY() + ui_data[(*it)]->getSizeY())));

			ci::gl::color(1, 1, 1, 1);
			textures[(*it)].disable();

			if (ui_data[(*it)]->getUIType() == UITYPE::GaugeUI) {
				ci::gl::color(ui_data[(*it)]->getColorR(), ui_data[(*it)]->getColorG(), ui_data[(*it)]->getColorB(), ui_data[(*it)]->getColorA());
				gauge_texture[(*it)].enableAndBind();

				ci::gl::drawSolidRect(
					ci::Rectf(ci::Vec2f(
						ui_data[(*it)]->gaugeGetPosX(),
						ui_data[(*it)]->gaugeGetPosY()),
						ci::Vec2f(
							ui_data[(*it)]->gaugeGetPosX() + ui_data[(*it)]->gaugeGetSizeX(),
							ui_data[(*it)]->gaugeGetPosY() + ui_data[(*it)]->gaugeGetSizeY())));

				gauge_texture[(*it)].disable();
				ci::gl::color(1, 1, 1, 1);
			}
		}
		else if (ui_data[(*it)]->getUIType() == UITYPE::FontUI ||
			ui_data[(*it)]->getUIType() == UITYPE::IncrementTimeUI ||
			ui_data[(*it)]->getUIType() == UITYPE::DecrementTimeUI) {
			
			ci::gl::pushModelView();
			ci::gl::translate(ui_data[(*it)]->fontGetPosX(), ui_data[(*it)]->fontGetPosY());
			ci::gl::drawString(ui_data[(*it)]->fontGetText(),
				ci::Vec2f(ui_data[(*it)]->getPosX(), ui_data[(*it)]->getPosY()),
				ci::ColorA(ui_data[(*it)]->getColorR(),
					ui_data[(*it)]->getColorG(),
					ui_data[(*it)]->getColorB(),
					ui_data[(*it)]->getColorA()),
				font[(*it)]);

			ci::gl::color(ci::Color::white());

			ci::gl::popModelView();
		}
	}
	ci::gl::popModelView();
}
