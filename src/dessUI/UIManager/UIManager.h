#pragma once
#include <memory>
#include <unordered_map>
#include "cinder/app/AppNative.h"
#include "jsoncpp/json/json.h"
#include "../UIs/CollisionUI/CollisionUI.h"
#include "../UIs/FontUI/FontUI.h"
#include "../UIs/GaugeUI/GaugeUI.h"
#include "../UIs/TextureUI/TextureUI.h"
#include "../UIs/IncrementTimeUI/IncrementTimeUI.h"
#include "../UIs/DecrementTimeUI/DecrementTimeUI.h"
#include "../UIs/AnimationUI/AnimationUI.h"
#include "../UIs/ScrollUI/ScrollUI.h"

namespace dess {
	enum class SceneName {
		TITLE,
		SELECT,
		GAMEMAIN,
		RESULT
	};
}
class UIManager
{
protected:
	std::unordered_map<std::string, int> easing_type;
	std::vector<std::string> ui_objects;
	std::vector<std::string> ui_scrolls_key;
	std::map<std::string,float> scroll_scales;
public:
	UIManager() {};

	std::unordered_map<std::string, std::shared_ptr<UIBase>> ui_data;
	void setEasing(const Json::Value& root,const std::string& it,const int& type);
	void JsonInit(const dess::SceneName& scene);
	void loadEasingType(const Json::Value& root_type);
};