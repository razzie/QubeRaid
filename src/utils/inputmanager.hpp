/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <cstdint>
#include <irrlicht.h>

class QubeRaid;

class InputManager : public irr::IEventReceiver
{
public:
	InputManager(QubeRaid*);
	virtual ~InputManager();
	virtual bool OnEvent(const irr::SEvent& event);
	bool isLeftMouseBtnDown() const;
	bool isMiddleMouseBtnDown() const;
	bool isRightMouseBtnDown() const;
	irr::core::vector2di getMousePosition() const;
	bool isKeyDown(irr::EKEY_CODE) const;

private:
	QubeRaid* m_app;
	bool m_keys[irr::KEY_KEY_CODES_COUNT];
	bool m_mousebtn_left;
	bool m_mousebtn_middle;
	bool m_mousebtn_right;
	int32_t m_last_mouse_x;
	int32_t m_last_mouse_y;
};
