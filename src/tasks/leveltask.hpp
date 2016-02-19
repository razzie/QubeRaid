/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <vector>
#include <irrlicht.h>
#include <gg/thread.hpp>

class Application;
//class GroundNode;
class TerrainNode;
//class QuboidNode;

class LevelTask : public gg::ITask
{
public:
	LevelTask(Application*);
	virtual ~LevelTask();
	virtual void onStart(gg::ITaskOptions&);
	virtual void onEvent(gg::ITaskOptions&, gg::EventPtr);
	virtual void onUpdate(gg::ITaskOptions&);
	virtual void onStateChange(gg::ITaskOptions&, gg::IThread::State old_state, gg::IThread::State new_state);
	virtual void onError(gg::ITaskOptions&, std::exception&);
	virtual void onFinish(gg::ITaskOptions&);

private:
	Application* m_app;
	//GroundNode* m_ground;
	//std::vector<QuboidNode*> m_quboids;
	TerrainNode* m_terrain;

	void resetCamera();
};
