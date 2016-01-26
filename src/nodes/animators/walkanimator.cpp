/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <cmath>
#include "nodes/animators/walkanimator.hpp"

using namespace irr;


WalkAnimator::WalkAnimator(scene::ISceneNode* node, const std::vector<core::vector2df>& path) :
	m_node(node),
	m_start_time(0)
{
	if (path.size() == 0) return;

	const float speed = 200.0f;

	m_path.reserve(path.size());

	for (unsigned i = 0; i < path.size() - 1; ++i)
	{
		Path p;
		p.m_start_point = path[i];
		p.m_end_point = path[i + 1];
		float dist = p.m_start_point.getDistanceFrom(p.m_end_point);
		p.m_start_time = ((i == 0) ? 0 : (m_path[i - 1].m_end_time));
		p.m_end_time = p.m_start_time + (u32)(dist * speed);

		m_path.push_back(p);
	}
}

WalkAnimator::WalkAnimator(scene::ISceneNode* node, const std::vector<Path>& path) :
	m_node(node),
	m_path(path.begin(), path.end()),
	m_start_time(0)
{
}

WalkAnimator::~WalkAnimator()
{
}

void WalkAnimator::animateNode(scene::ISceneNode* node, u32 timeMs)
{
	if (node != m_node || m_path.empty())
		return;

	if (m_start_time == 0)
		m_start_time = timeMs;

	u32 elapsed = timeMs - m_start_time;
	u32 travel_interval = m_path[m_path.size() - 1].m_end_time;
	f32 jump = 0.25f * (f32)std::sin(0.025f * elapsed) + 0.25f;

	for (auto& path : m_path)
	{
		if (path.m_start_time <= elapsed &&
			path.m_end_time > elapsed)
		{
			core::vector2df pos = path.getPointByTime(elapsed);
			node->setPosition({ pos.X, jump, pos.Y });
			return;
		}
	}

	auto pos = node->getPosition();
	pos.Y = jump;
	node->setPosition(pos);

	if (pos.Y < 0.2f)
		node->removeAnimator(this);
}

scene::ISceneNodeAnimator* WalkAnimator::createClone(scene::ISceneNode* node, scene::ISceneManager* newManager)
{
	return new WalkAnimator(node, m_path);
}

//bool WalkAnimator::hasFinished() const
//{
//	if (m_path.empty())
//		true;
//
//	uint32_t travel_interval = m_path[m_path.size() - 1].m_end_time;
//	return (m_elapsed > travel_interval);
//}

core::vector2df WalkAnimator::Path::getPointByTime(u32 elapsed) const
{
	if (elapsed <= m_start_time)
		return m_start_point;
	else if (elapsed >= m_end_time)
		return m_end_point;

	u32 duration = m_end_time - m_start_time;
	u32 elapsed_from_start = elapsed - m_start_time;

	core::vector2df path_movement = m_end_point - m_start_point;

	core::vector2df mid_point = m_start_point;
	mid_point += (path_movement * ((float)elapsed_from_start / (float)duration));

	return mid_point;
}
