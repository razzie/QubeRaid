/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <irrlicht.h>
#include "events/inputevents.hpp"
#include "utils/inputmanager.hpp"
#include "quberaid.hpp"

using namespace irr;


struct KeyInputEx : KeyInput
{
	KeyInputEx(const SEvent::SKeyInput& input)
	{
		character = input.Char;
		key_code = static_cast<uint16_t>(input.Key);
		pressed_down = input.PressedDown;
		shift = input.Shift;
		control = input.Control;
		consumed = false;
	}
};

struct MouseInputEx : public MouseInput
{
	MouseInputEx(const SEvent::SMouseInput& input, InputManager* mgr = nullptr)
	{
		x = input.X;
		y = input.Y;
		x_delta = input.X - (mgr ? mgr->getMousePosition().X : 0);
		y_delta = input.Y - (mgr ? mgr->getMousePosition().Y : 0);
		wheel = input.Wheel;
		shift = input.Shift;
		control = input.Control;
		left_button_down = input.isLeftPressed();
		left_button_clicked = mgr && input.isLeftPressed() && !mgr->isLeftMouseBtnDown();
		right_button_down = input.isRightPressed();
		right_button_clicked = mgr && input.isRightPressed() && !mgr->isRightMouseBtnDown();
		middle_button_down = input.isMiddlePressed();
		middle_button_clicked = mgr && input.isMiddlePressed() && !mgr->isMiddleMouseBtnDown();
		consumed = false;
	}
};

struct GUIActionEx : public GUIAction
{
	GUIActionEx(const SEvent::SGUIEvent& input)
	{
		caller = makeIrrPtr(input.Caller);
		element = makeIrrPtr(input.Element);
		action = static_cast<uint16_t>(input.EventType);
	}
};


InputManager::InputManager(QubeRaid* app) :
	m_app(app),
	m_last_mouse_x(0),
	m_last_mouse_y(0)
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
	{
		m_keys[i] = false;
	}
}

InputManager::~InputManager()
{
}

bool InputManager::OnEvent(const SEvent& event)
{
	switch (event.EventType)
	{
	case EET_KEY_INPUT_EVENT:
		m_app->sendEvent(key_event(KeyInputEx(event.KeyInput)));
		m_keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
		return false;

	case EET_MOUSE_INPUT_EVENT:
		{
			m_app->sendEvent(mouse_event(MouseInputEx(event.MouseInput, this)));
			m_mousebtn_left = event.MouseInput.isLeftPressed();
			m_mousebtn_middle = event.MouseInput.isMiddlePressed();
			m_mousebtn_right = event.MouseInput.isRightPressed();
			m_last_mouse_x = event.MouseInput.X;
			m_last_mouse_y = event.MouseInput.Y;
		}
		return false;

	case EET_GUI_EVENT:
		m_app->sendEvent(gui_event(GUIActionEx(event.GUIEvent)));
		return false;

	default:
		return false;
	}
}

bool InputManager::isLeftMouseBtnDown() const
{
	return m_mousebtn_left;
}

bool InputManager::isMiddleMouseBtnDown() const
{
	return m_mousebtn_middle;
}

bool InputManager::isRightMouseBtnDown() const
{
	return m_mousebtn_right;
}

core::vector2di InputManager::getMousePosition() const
{
	return { m_last_mouse_x, m_last_mouse_y };
}

bool InputManager::isKeyDown(EKEY_CODE keyCode) const
{
	return (m_keys[keyCode]);
}
