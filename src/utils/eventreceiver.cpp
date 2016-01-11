/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <irrlicht.h>
#include "events.hpp"
#include "utils/eventreceiver.hpp"
#include "quberaid.hpp"


struct KeyInputEx : KeyInput
{
	KeyInputEx(const irr::SEvent::SKeyInput& input)
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
	MouseInputEx(const irr::SEvent::SMouseInput& input, irr::core::vector2di delta = {})
	{
		x = input.X;
		y = input.Y;
		x_delta = delta.X;
		y_delta = delta.Y;
		wheel = input.Wheel;
		shift = input.Shift;
		control = input.Control;
		left_button = input.isLeftPressed();
		right_button = input.isRightPressed();
		middle_button = input.isMiddlePressed();
		consumed = false;
	}
};

struct GUIActionEx : public GUIAction
{
	GUIActionEx(const irr::SEvent::SGUIEvent& input)
	{
		caller = makeIrrPtr(input.Caller);
		element = makeIrrPtr(input.Element);
		action = static_cast<uint16_t>(input.EventType);
	}
};


EventReceiver::EventReceiver(QubeRaid* app) :
	m_app(app),
	m_last_mouse_x(0),
	m_last_mouse_y(0)
{
}

EventReceiver::~EventReceiver()
{
}

bool EventReceiver::OnEvent(const irr::SEvent& event)
{
	switch (event.EventType)
	{
	case irr::EET_KEY_INPUT_EVENT:
		m_app->sendEvent(key_event(KeyInputEx(event.KeyInput)));
		return false;

	case irr::EET_MOUSE_INPUT_EVENT:
		{
			irr::core::vector2di delta(event.MouseInput.X - m_last_mouse_x, event.MouseInput.Y - m_last_mouse_y);
			m_last_mouse_x = event.MouseInput.X;
			m_last_mouse_y = event.MouseInput.Y;
			m_app->sendEvent(mouse_event(MouseInputEx(event.MouseInput, delta)));
		}
		return false;

	case irr::EET_GUI_EVENT:
		m_app->sendEvent(gui_event(GUIActionEx(event.GUIEvent)));
		return false;

	default:
		return false;
	}
}
