#pragma once
#include <functional>
#include <memory>
#include "cinder/app/App.h"
#include "SceneBase.h"
#include "Title/Title.h"
#include "GameMain/GameMain.h"
#include "Result/Result.h"
#define SCENE SceneManager::get()
class SceneManager {
public:

	SceneManager();
	~SceneManager() {
        delete scene;
	}
	
	SceneBase* scene;
	void setup();
	void update(const float& delta_time);
	void draw();
	void shift(const SceneName& scene);
	void keyDown(const ci::app::KeyEvent& event);
	void keyUp(const ci::app::KeyEvent& event);
	void mouseDown(const ci::app::MouseEvent& event);
	void mouseMove(const ci::app::MouseEvent& event);
	void mouseDrag(const ci::app::MouseEvent& event);
	void mouseUp(const ci::app::MouseEvent& event);

	static SceneManager& get() {
		static SceneManager scene;
		return scene;
	}
};
