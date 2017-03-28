#pragma once
#include "../SceneBase.h"
#include "../SceneManager.h"

class ResultUI;
class Result : public SceneBase
{
private:
	std::shared_ptr<ResultUI> ui;
	bool result;
public:
	Result() {}
	Result(const bool& result) {
		this->result = result;
	}
	void setup() override;
	void update(const float& delta_time) override ;
	void draw() override;
	
	
};