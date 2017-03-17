#include "Input.h"
#include "../../Objects/Camera/Camera.h"

InputAll::InputAll() {
	cursor_captured = false;
	serch.insert(std::make_pair("Horizontal_WS", ci::app::KeyEvent::KEY_w));
	serch.insert(std::make_pair("Horizontal_AD", ci::app::KeyEvent::KEY_d));
}

void InputAll::keyDown(const ci::app::KeyEvent& event) {
	press.insert(event.getCode());
	push.insert(event.getCode());
}
void InputAll::keyUp(const ci::app::KeyEvent& event)
{
	pull.insert(event.getCode());
	press.erase(press.find(event.getCode()));
}

void mouseCursolFixed(const ci::app::MouseEvent& event, ci::Vec2f& inc_pos,
	ci::Vec2f& mouse_pos, bool& cursor_captured,POINT& last_cursor_pos) {
	
	if (cursor_captured) {
		POINT pt;
		
		GetCursorPos(&pt);
		POINT delta;
		delta.x = pt.x - last_cursor_pos.x;
		delta.y = pt.y - last_cursor_pos.y;
		
		if (delta.x != 0 && delta.y != 0) {
			SetCursorPos(last_cursor_pos.x, last_cursor_pos.y);
			CAMERA.incliment_camera_angle(ci::Vec2f(delta.x, delta.y));
		}
		

	}
	else {

		SetCursorPos(ci::app::getWindowPos().x + (ci::app::getWindowSize().x / 2),
			ci::app::getWindowPos().y + (ci::app::getWindowSize().y / 2));
		GetCursorPos(&last_cursor_pos);
		mouse_pos.x = last_cursor_pos.x;
		mouse_pos.y = last_cursor_pos.y;
		cursor_captured = true;
	}
}

void InputAll::mouseMove(const ci::app::MouseEvent& event)
{

	mouseCursolFixed(event, inc_pos, mouse_pos, cursor_captured, last_cursor_pos);


}
void InputAll::mouseDrag(const ci::app::MouseEvent& event)
{

	mouseCursolFixed(event, inc_pos, mouse_pos, cursor_captured,last_cursor_pos);

}





void InputAll::mouseDown(const ci::app::MouseEvent& event)
{
	if (event.isLeft())
	{
		press.insert(ci::app::MouseEvent::LEFT_DOWN);
		push.insert(ci::app::MouseEvent::LEFT_DOWN);
	}
	if (event.isRight())
	{
		press.insert(ci::app::MouseEvent::RIGHT_DOWN);
		push.insert(ci::app::MouseEvent::RIGHT_DOWN);
	}
	if (event.isMiddle())
	{
		press.insert(ci::app::MouseEvent::MIDDLE_DOWN);
		push.insert(ci::app::MouseEvent::MIDDLE_DOWN);
	}
}

void InputAll::mouseUp(const ci::app::MouseEvent& event)
{
	if (event.isLeft())
	{
		pull.insert(ci::app::MouseEvent::LEFT_DOWN);
		press.erase(ci::app::MouseEvent::LEFT_DOWN);
	}
	if (event.isRight())
	{
		pull.insert(ci::app::MouseEvent::RIGHT_DOWN);
		press.erase(ci::app::MouseEvent::RIGHT_DOWN);
	}
	if (event.isMiddle())
	{
		pull.insert(ci::app::MouseEvent::MIDDLE_DOWN);
		press.erase(ci::app::MouseEvent::MIDDLE_DOWN);
	}
}


float InputAll::getAxis(std::string axis_name_, const float & velocity_)
{
	if (serch.find(axis_name_) == serch.end())
		assert(!"Not axis name");
	int press_key = serch.find(axis_name_)->second;
	if (keys.find(press_key) == keys.end())
	{
		if (press_key == ci::app::KeyEvent::KEY_RIGHT)
			keys.insert(std::make_pair(press_key, ci::app::KeyEvent::KEY_LEFT));
		if (press_key == ci::app::KeyEvent::KEY_UP)
			keys.insert(std::make_pair(press_key, ci::app::KeyEvent::KEY_DOWN));
		if (press_key == ci::app::KeyEvent::KEY_w)
			keys.insert(std::make_pair(press_key, ci::app::KeyEvent::KEY_s));
		if (press_key == ci::app::KeyEvent::KEY_d)
			keys.insert(std::make_pair(press_key, ci::app::KeyEvent::KEY_a));
		axis_value.insert(std::make_pair(axis_name_, 0.0f));
	}
	else
	{
		if (pressKey(press_key))
		{
			axis_value.find(axis_name_)->second += velocity_;
			axis_value.find(axis_name_)->second = std::min(axis_value.find(axis_name_)->second, 1.0f);
		}
		else if (pressKey(keys.find(press_key)->second))
		{
			axis_value.find(axis_name_)->second -= velocity_;
			axis_value.find(axis_name_)->second = std::max(axis_value.find(axis_name_)->second, -1.0f);
		}
		else
		{
			if (axis_value.find(axis_name_)->second < 0)
				axis_value.find(axis_name_)->second += velocity_;
			if (axis_value.find(axis_name_)->second > 0)
				axis_value.find(axis_name_)->second -= velocity_;

			if (axis_value.find(axis_name_)->second < velocity_ &&
				axis_value.find(axis_name_)->second > -velocity_)
				axis_value.find(axis_name_)->second = 0;
		}
	}
	return axis_value.find(axis_name_)->second;
}

bool InputAll::pressKey(const int& pressed_key) {
	if (press.find(pressed_key) != press.end()) {
		return true;
	}
	return false;
}

bool InputAll::pushKey(const int & pressed_key)
{
	if (push.find(pressed_key) == push.end())
		return false;
	push.erase(push.find(pressed_key));
	return true;
}

bool InputAll::pullKey(const int & pressed_key)
{
	if (pull.find(pressed_key) == pull.end())
		return false;
	pull.erase(pull.find(pressed_key));
	return true;
}

void InputAll::flashInput()
{
	push.clear();
	pull.clear();
}






