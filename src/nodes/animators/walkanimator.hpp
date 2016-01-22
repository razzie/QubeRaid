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

class WalkAnimator : public irr::scene::ISceneNodeAnimator
{
public:
	WalkAnimator(irr::scene::ISceneNode* node, const std::vector<irr::core::vector2df>& path);
	virtual ~WalkAnimator();
	virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
	virtual ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager = 0);
	virtual bool hasFinished() const;

private:
	struct Path
	{
		irr::core::vector2df m_start_point;
		irr::core::vector2df m_end_point;
		irr::core::vector2df m_velocity;
		irr::u32 m_start_time;
		irr::u32 m_end_time;

		irr::core::vector2df getPointByTime(irr::u32) const;
	};

	irr::scene::ISceneNode* m_node;
	std::vector<irr::core::vector2df> m_path;
	std::vector<Path> m_built_path;
	irr::u32 m_elapsed;

	void buildPath();
};
