#include "SceneManager.h"
#include "../Utility/Input/Input.h"
SceneManager::SceneManager() {
	scene = new GameMain();
}

void SceneManager::setup()
{
	scene->setup();
}


void SceneManager::update(const float& delta_time)
{
	scene->update(delta_time);
}

void SceneManager::draw()
{
	scene->draw();
}

void SceneManager::shift(const SceneName& scene_name)
{
	delete scene;
	switch (scene_name) {
	case SceneName::TITLE:
		scene = new Title();
		scene->setup();
		break;
	case SceneName::GAMEMAIN:
		scene = new GameMain();
		scene->setup();
		break;
	case SceneName::RESULT:
		scene = new Result();
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

