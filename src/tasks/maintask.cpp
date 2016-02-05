/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <gg/logger.hpp>
#include <irrlicht.h>
#include "quberaid.hpp"
#include "events/inputevents.hpp"
#include "tasks/cameracontroller.hpp"
#include "tasks/maintask.hpp"
#include "utils/inputmanager.hpp"
#include "materials/linematerial.hpp"

using namespace irr;


static void takeScreenshot(irr::IrrlichtDevice* device)
{
	irr::video::IVideoDriver* const driver = device->getVideoDriver();

	//get image from the last rendered frame 
	irr::video::IImage* const image = driver->createScreenShot();
	if (image) //should always be true, but you never know. ;) 
	{
		//construct a filename, consisting of local time and file extension 
		irr::c8 filename[64];
		snprintf(filename, 64, "screenshot_%u.png", device->getTimer()->getRealTime());

		//write screenshot to file 
		if (!driver->writeImageToFile(image, filename))
			device->getLogger()->log(L"Failed to take screenshot.", irr::ELL_WARNING);

		//Don't forget to drop image since we don't need it anymore. 
		image->drop();
	}
}


MainTask::MainTask(QubeRaid* app) :
	m_app(app),
	m_device(m_app->getDevice()),
	m_driver(m_app->getDriver()),
	m_smgr(m_app->getSceneManager()),
	m_cam(m_app->getCamera()),
	m_mouse(app)
{
	m_device->getCursorControl()->setVisible(false);
}

MainTask::~MainTask()
{
}

void MainTask::onStart(gg::ITaskOptions& options)
{
	options.subscribe(key_event);
}

void MainTask::onEvent(gg::ITaskOptions& options, gg::EventPtr e)
{
	if (e->is(key_event))
	{
		const KeyInput* event;
		e->get(event);

		if (!event->consumed)
		{
			EKEY_CODE key = static_cast<EKEY_CODE>(event->key_code);
			switch (key)
			{
			case EKEY_CODE::KEY_ESCAPE:
				options.getThread().finish();
				event->consumed = true;
				break;

			case EKEY_CODE::KEY_KEY_R:
				break;

			case EKEY_CODE::KEY_F12:
				takeScreenshot(m_device);
				event->consumed = true;
				break;
			}
		}
	}
}

void MainTask::onUpdate(gg::ITaskOptions& options)
{
	if (m_device->run())
	{
		//m_driver->beginScene(true, true, { 255, 128, 196, 255 });
		//m_driver->beginScene(true, true, { 255, 196, 196, 196 });
		//m_driver->beginScene(true, true, { 255, 64, 64, 64 });
		//m_driver->beginScene(true, true, { 255, 255, 255, 255 });
		m_driver->beginScene(true, true, { 255, 255, 196, 128 });
		m_smgr->drawAll();

		//m_driver->setMaterial(LineMaterial());
		//m_driver->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
		//m_driver->draw3DLine({ 0.f,0.f,0.f }, { 1.f,0.f,0.f }, 0xffff0000);
		//m_driver->draw3DLine({ 0.f,0.f,0.f }, { 0.f,1.f,0.f }, 0xff00ff00);
		//m_driver->draw3DLine({ 0.f,0.f,0.f }, { 0.f,0.f,1.f }, 0xff0000ff);

		m_mouse.render();

		m_driver->endScene();
	}
	else
	{
		options.getThread().finish();
	}
}

void MainTask::onStateChange(gg::ITaskOptions& options, gg::IThread::State old_state, gg::IThread::State new_state)
{
}

void MainTask::onError(gg::ITaskOptions& options, std::exception& e)
{
	gg::log << e.what() << std::endl;
}

void MainTask::onFinish(gg::ITaskOptions& options)
{
}
