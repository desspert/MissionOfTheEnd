#pragma once
#include "../SceneBase.h"
#include "../SceneManager.h"
#include "../../dessUI/UIPlate/SelectUI/SelectUI.h"
#include "../../SoundManager.h"
#include "../../Event/Coroutine.h"
#include "../../Animation/Production/GasyaSpawn/GasyaSpawn.h"
#include "../../Animation/Production/GasyaEnd/GasyaEnd.h"
#include<memory>
namespace select_ {
	enum WINDOW_SIZE {
		WINDOW_WIDTH = 640,
		WINDOW_HEIGHT = 960
	};
}
 
class Select : public SceneBase
{ 
private:
	SelectUI ui;
	ci::vec2 camera_pos;

	std::vector<CoroutineInfo> c_info;
	float time;
	int releaseChara;
	bool pause;
	bool is_start;
	bool gasya_production;
public:
	Select();
    ~Select(){
        
    }
	struct _coroutine;
	std::shared_ptr<_coroutine> _m;

	void setup() override;
	void update(const float& delta_time) override ;
	void draw() override ;
	void mouseDown(const ci::app::MouseEvent& event);
	void mouseDrag(const ci::app::MouseEvent& event);
	void mouseUp(const ci::app::MouseEvent& event);
	void touchesBegan(ci::app::TouchEvent event);
	void touchesMoved(ci::app::TouchEvent event);
	void touchesEnded(ci::app::TouchEvent event);
	
};
