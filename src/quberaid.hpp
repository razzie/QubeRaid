/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <memory>
#include <gg/thread.hpp>

namespace irr
{
	class IrrlichtDevice;

	namespace video
	{
		class IVideoDriver;
	};

	namespace scene
	{
		class ISceneManager;
		class ICameraSceneNode;
	};
};

template<class T>
std::shared_ptr<T> makeIrrPtr(T* p)
{
	p->grab();
	return std::shared_ptr<T>(p, [](T* p) { p->drop(); });
}

class InputManager;
class MaterialFactory;

class QubeRaid
{
public:
	enum State : uint16_t
	{
		MENU,
		GAME
	};

	QubeRaid(int argc, char** argv);
	QubeRaid();
	int run();
	void sendEvent(gg::EventPtr);
	irr::IrrlichtDevice* getDevice();
	irr::video::IVideoDriver* getDriver();
	irr::scene::ISceneManager* getSceneManager();
	irr::scene::ICameraSceneNode* getCamera();
	InputManager* getInputManager();
	MaterialFactory* getMaterialFactory();

private:
	gg::ThreadPtr m_thread;
	irr::IrrlichtDevice* m_device;
	irr::video::IVideoDriver* m_driver;
	irr::scene::ISceneManager* m_smgr;
	irr::scene::ICameraSceneNode* m_cam;
	InputManager* m_inputmgr;
	MaterialFactory* m_matfactory;
};
