/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <irrlicht.h>
#include "quberaid.hpp"
#include "utils/inputmanager.hpp"
#include "utils/materialfactory.hpp"
#include "tasks/maintask.hpp"
#include "tasks/cameracontroller.hpp"
#include "nodes/groundnode.hpp"

using namespace irr;


QubeRaid::QubeRaid(int argc, char** argv) :
	m_thread(gg::threadmgr.createThread("Main"))
{
	SIrrlichtCreationParameters params; // constructor sets the defaults
	params.AntiAlias = 16;
	params.Bits = 32;
	//params.DriverType = video::EDT_DIRECT3D9;
	params.DriverType = video::EDT_OPENGL;
	params.Fullscreen = false;
	params.WindowSize = core::dimension2du(1280, 800);
	params.WithAlphaChannel = true;
	params.Vsync = true;

	m_device = createDeviceEx(params);
	m_driver = m_device->getVideoDriver();
	m_smgr = m_device->getSceneManager();
	m_inputmgr = new InputManager(this);
	m_matfactory = new MaterialFactory(this);

	m_device->setEventReceiver(m_inputmgr);
	m_device->setResizable(true);
	m_device->setWindowCaption(L"QubeRaid");

	m_cam = m_smgr->addCameraSceneNode(0, core::vector3df(0.f, 10.f, -10.f), core::vector3df(0.f, 0.f, 0.f));
	//m_smgr->addLightSceneNode(0, { 0.f, 30.f, 30.f }, { 255, 255, 255, 255 }, 0.5f);
	//m_smgr->addCubeSceneNode();
	GroundNode* ground = new GroundNode(this);
}

QubeRaid::QubeRaid()
{
}

int QubeRaid::run()
{
	m_thread->setState(State::GAME);
	m_thread->addTask<MainTask, State::GAME>(this);
	m_thread->addTask<CameraController, State::GAME>(this);
	return m_thread->run(gg::IThread::Mode::LOCAL);
}

void QubeRaid::sendEvent(gg::EventPtr event)
{
	m_thread->sendEvent(event);
}

irr::IrrlichtDevice* QubeRaid::getDevice()
{
	return m_device;
}

irr::video::IVideoDriver* QubeRaid::getDriver()
{
	return m_driver;
}

irr::scene::ISceneManager* QubeRaid::getSceneManager()
{
	return m_smgr;
}

irr::scene::ICameraSceneNode* QubeRaid::getCamera()
{
	return m_cam;
}

MaterialFactory* QubeRaid::getMaterialFactory()
{
	return m_matfactory;
}
