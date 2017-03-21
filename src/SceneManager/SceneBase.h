#pragma once
namespace game {
	enum class SceneName {
		TITLE,
		SELECT,
		GAMEMAIN,
		RESULT
	};
}
class SceneBase {
public:
	SceneBase() {}
	~SceneBase(){};
	virtual void update(const float& delta_time) {};
	virtual void draw() {};
	virtual void setup() {};
	virtual void shift(const game::SceneName& scene) {};
};