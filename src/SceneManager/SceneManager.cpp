#include "SceneManager.h"
#include "../Utility/Input/Input.h"
#include "../Utility/Easing/Easing.h"
#include "../Objects/Camera/Camera.h"
#include "../Utility/SoundManager.h"
SceneManager::SceneManager() {
	scene = std::make_unique<Title>();
}

void SceneManager::setup()
{
	scene->setup();
	CAMERA.setup();
	SE.setup();
}


void SceneManager::update(const float& delta_time)
{
	scene->update(delta_time);
	CAMERA.shake(delta_time);
}

void SceneManager::draw()
{
	scene->draw();
	ENV.flashInput();
	c_Easing::update();
}

void SceneManager::shift(const game::SceneName& scene_name)
{
	switch (scene_name) {
	case game::SceneName::TITLE:
		SceneManager::get().scene = std::make_unique<Title>();
		SceneManager::get().scene->setup();
		break;
	case game::SceneName::GAMEMAIN:
		SceneManager::get().scene = std::make_unique<GameMain>();
		SceneManager::get().scene->setup();
		break;
	case game::SceneName::RESULT:
		SceneManager::get().scene = std::make_unique<Result>();
		SceneManager::get().scene->setup();
		break;
	}
}

void SceneManager::shift(const game::SceneName & scene_name, const bool & result)
{
	switch (scene_name) {
	case game::SceneName::TITLE:
		SceneManager::get().scene = std::make_unique<Title>();
		SceneManager::get().scene->setup();
		break;
	case game::SceneName::GAMEMAIN:
		SceneManager::get().scene = std::make_unique<GameMain>();
		SceneManager::get().scene->setup();
		break;
	case game::SceneName::RESULT:
		SceneManager::get().scene = std::make_unique<Result>(result);
		SceneManager::get().scene->setup();
		break;
	}
}

void SceneManager::keyDown(const ci::app::KeyEvent & event)
{
	ENV.keyDown(event);
}

void SceneManager::keyUp(const ci::app::KeyEvent & event)
{
	ENV.keyUp(event);
}

void SceneManager::mouseDown(const ci::app::MouseEvent& event)
{
	ENV.mouseDown(event);
}

void SceneManager::mouseMove(const ci::app::MouseEvent & event)
{
	ENV.mouseMove(event);
}

void SceneManager::mouseDrag(const ci::app::MouseEvent& event)
{
	ENV.mouseDrag(event);
}

void SceneManager::mouseUp(const ci::app::MouseEvent& event)
{
	ENV.mouseUp(event);
}

