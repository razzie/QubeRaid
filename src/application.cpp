/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <irrlicht.h>
#include "application.hpp"
#include "utils/inputmanager.hpp"
#include "tasks/maintask.hpp"
#include "tasks/leveltask.hpp"
#include "tasks/cameracontroller.hpp"

using namespace irr;


Application::Application(int argc, char** argv) :
	m_thread(gg::threadmgr.createThread("Main")),
	m_resources(gg::res.createResourcePool())
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

	m_device->setEventReceiver(m_inputmgr);
	m_device->setResizable(true);
	m_device->setWindowCaption(L"Application");

	m_cam = m_smgr->addCameraSceneNode(0, core::vector3df(0.f, 10.f, -10.f), core::vector3df(0.f, 0.f, 0.f));
	//m_smgr->addLightSceneNode(0, { 0.f, 30.f, 30.f }, { 255, 255, 255, 255 }, 0.5f);
	//m_smgr->addCubeSceneNode();

	initResources();
}

Application::Application()
{
	// m_device takes care of m_inputmgr
	m_device->drop();
}

int Application::run()
{
	m_thread->setState(State::GAME);
	m_thread->addTask<MainTask, State::GAME>(this);
	m_thread->addTask<LevelTask, State::GAME>(this);
	m_thread->addTask<CameraController, State::GAME>(this);
	return m_thread->run(gg::IThread::Mode::LOCAL);
}

irr::IrrlichtDevice* Application::getDevice()
{
	return m_device;
}

irr::video::IVideoDriver* Application::getDriver()
{
	return m_driver;
}

irr::scene::ISceneManager* Application::getSceneManager()
{
	return m_smgr;
}

irr::scene::ICameraSceneNode* Application::getCamera()
{
	return m_cam;
}

gg::ResourcePoolPtr Application::getResources()
{
	return m_resources;
}

InputManager* Application::getInputManager()
{
	return m_inputmgr;
}

void Application::sendEvent(gg::EventPtr event)
{
	m_thread->sendEvent(event);
}

std::shared_ptr<Level> Application::getLevel() const
{
	return m_level;
}

void Application::setLevel(std::shared_ptr<Level> level)
{
	m_level = level;
}


/** --- RESOURCES --- */

#include "materials/linematerial.hpp"
#include "materials/outlinematerial.hpp"
#include "materials/flatmaterial.hpp"
#include "materials/cellmaterial.hpp"
#include "meshes/cubemesh.hpp"
#include "meshes/roundedcubemesh.hpp"

void Application::initResources()
{
	m_resources->add<LineMaterial>("material_line");
	m_resources->add<OutlineMaterial>("material_outline", this);
	m_resources->add<FlatMaterial>("material_flat", this);
	m_resources->add<CellMaterial>("material_cell", this);

	m_resources->add<CubeMesh>("mesh_cube");
	m_resources->add<RoundedCubeMesh>("mesh_roundedcube");
}
