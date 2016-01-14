/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <vector>
#include <utility> // std::pair
#include <irrlicht.h>
#include <gg/thread.hpp>

class QubeRaid;
class GroundNode;

class LevelTask : public gg::ITask
{
public:
	LevelTask(QubeRaid*);
	virtual ~LevelTask();
	virtual void onStart(gg::ITaskOptions&);
	virtual void onEvent(gg::ITaskOptions&, gg::EventPtr);
	virtual void onUpdate(gg::ITaskOptions&);
	virtual void onStateChange(gg::ITaskOptions&, gg::IThread::State old_state, gg::IThread::State new_state);
	virtual void onError(gg::ITaskOptions&, std::exception&);
	virtual void onFinish(gg::ITaskOptions&);

private:
	QubeRaid* m_app;
	unsigned m_level_radius;
	unsigned m_base_count;
	std::vector<irr::core::vector3df> m_base_positions;
	GroundNode* m_ground;
	std::vector<std::pair<irr::core::vector3di, irr::core::vector3di>> m_ground_blocks;

	void generateBasePositions();
	void generateGroundBlocks(unsigned seed);
	float getClosestBaseDistance(irr::core::vector3df pos) const;
};
