/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <gg/thread.hpp>
#include "utils/mousepointer.hpp"

class Application;

class MainTask : public gg::ITask
{
public:
	MainTask(Application*);
	virtual ~MainTask();
	virtual void onStart(gg::ITaskOptions&);
	virtual void onEvent(gg::ITaskOptions&, gg::EventPtr);
	virtual void onUpdate(gg::ITaskOptions&);
	virtual void onStateChange(gg::ITaskOptions&, gg::IThread::State old_state, gg::IThread::State new_state);
	virtual void onError(gg::ITaskOptions&, std::exception&);
	virtual void onFinish(gg::ITaskOptions&);

private:
	Application* m_app;
	irr::IrrlichtDevice* m_device;
	irr::video::IVideoDriver* m_driver;
	irr::scene::ISceneManager* m_smgr;
	irr::scene::ICameraSceneNode* m_cam;
	MousePointer m_mouse;
};
