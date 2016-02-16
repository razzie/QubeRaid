/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <irrlicht.h>

class Application;

class MousePointer
{
public:
	MousePointer(Application*);
	~MousePointer();
	void render();

private:
	Application* m_app;
	irr::core::vector2di m_mouse_back_pos;
	irr::video::ITexture* m_texture;
};
