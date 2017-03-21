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
	
}

void SceneManager::draw()
{
	scene->draw();
	ENV.flashInput();
	c_Easing::update();
}

void SceneManager::shift(const SceneName& scene_name)
{
	switch (scene_name) {
	case SceneName::TITLE:
		scene = std::make_unique<Title>();
		scene->setup();
		break;
	case SceneName::GAMEMAIN:
		scene = std::make_unique<GameMain>();
		scene->setup();
		break;
	case SceneName::RESULT:
		scene = std::make_unique<Result>();
		scene->setup();
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

