/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <gg/thread.hpp>

class QubeRaid;

class CameraController : public gg::ITask
{
public:
	CameraController(QubeRaid*);
	virtual ~CameraController();
	virtual void onStart(gg::ITaskOptions&);
	virtual void onEvent(gg::ITaskOptions&, gg::EventPtr);
	virtual void onUpdate(gg::ITaskOptions&);

private:
	QubeRaid* m_app;
};
