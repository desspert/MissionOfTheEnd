#pragma once

#include <iostream>
#include <unordered_map>
#include <set>
#include "cinder/app/AppNative.h"

#define ENV InputAll::get()

class InputAll
{
private:
	std::set<int> press;
	std::set<int> push;
	std::set<int> pull;
	ci::Vec2f mouse_pos;
	ci::Vec2f inc_pos;
	bool mouse_left_press;
	bool mouse_right_press;
	bool cursor_captured;
	POINT last_cursor_pos;
public:
	InputAll();
	static InputAll& get() {
		static InputAll in;
		return in;
	}

	ci::Vec2f getIncPos() {
		return inc_pos;
	}
	void setIncPos(ci::Vec2f set) {
		inc_pos = set;
	}

	void keyDown(const ci::app::KeyEvent& event);
	void keyUp(const ci::app::KeyEvent& event);
	void mouseDown(const ci::app::MouseEvent& event);
	void mouseUp(const ci::app::MouseEvent& event);
	void mouseMove(const ci::app::MouseEvent& event);
	void mouseDrag(const ci::app::MouseEvent& event);


	std::unordered_map<std::string, int> serch;
	std::unordered_map<int, int> keys;
	std::unordered_map<std::string, float> axis_value;
	float getAxis(std::string axis_name, const float& velocity = 0.3);
	

	bool pressKey(const int& pressed_key);
	bool pushKey(const int& pressed_key);
	bool pullKey(const int& pressed_key);

	void flashInput();
};