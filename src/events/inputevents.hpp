/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <cstdint>
#include <memory>
#include <gg/event.hpp>

namespace irr
{
	namespace gui
	{
		class IGUIElement;
	};
};

struct KeyInput;
struct KeyInput : public gg::IEvent::Tag<0, KeyInput>
{
	wchar_t character;
	uint16_t key_code; // irr::EKEY_CODE
	unsigned pressed_down : 1;
	unsigned shift : 1;
	unsigned control : 1;
	mutable volatile unsigned consumed : 1;
};

struct MouseInput;
struct MouseInput : public gg::IEvent::Tag<0, MouseInput>
{
	int32_t x;
	int32_t y;
	int32_t x_delta;
	int32_t y_delta;
	float wheel;
	unsigned shift : 1;
	unsigned control : 1;
	unsigned left_button_down : 1;
	unsigned left_button_clicked : 1;
	unsigned right_button_down : 1;
	unsigned right_button_clicked : 1;
	unsigned middle_button_down : 1;
	unsigned middle_button_clicked : 1;
	mutable volatile unsigned consumed : 1;
};

struct GUIAction;
struct GUIAction : public gg::IEvent::Tag<0, GUIAction>
{
	std::shared_ptr<irr::gui::IGUIElement> caller;
	std::shared_ptr<irr::gui::IGUIElement> element;
	uint16_t action;
};

extern gg::IEventDefinition<KeyInput>& key_event;
extern gg::IEventDefinition<MouseInput>& mouse_event;
extern gg::IEventDefinition<GUIAction>& gui_event;
