/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <gg/thread.hpp>

class Application;

class CameraController : public gg::ITask
{
public:
	CameraController(Application*);
	virtual ~CameraController();
	virtual void onStart(gg::ITaskOptions&);
	virtual void onEvent(gg::ITaskOptions&, gg::EventPtr);
	virtual void onUpdate(gg::ITaskOptions&);

private:
	Application* m_app;
};
