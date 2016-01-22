/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "nodes/animators/walkanimator.hpp"

using namespace irr;


WalkAnimator::WalkAnimator(scene::ISceneNode* node, const std::vector<core::vector2df>& path) :
	m_node(node),
	m_elapsed(0)
{
	m_path.push_back({ node->getPosition().X, node->getPosition().Y }); // push node position to front
	for (auto& p : path) m_path.push_back(p);
	buildPath();
}

WalkAnimator::~WalkAnimator()
{
}

void WalkAnimator::animateNode(scene::ISceneNode* node, u32 timeMs)
{
	if (node != m_node || m_built_path.empty())
		return;

	m_elapsed += timeMs;

	uint32_t travel_interval = m_built_path[m_built_path.size() - 1].m_end_time;
	uint32_t aligned_elapsed;

	aligned_elapsed = m_elapsed % (travel_interval * 2);

	if (aligned_elapsed > travel_interval)
		aligned_elapsed = travel_interval - (aligned_elapsed - travel_interval);

	for (auto& path : m_built_path)
	{
		if (path.m_start_time <= aligned_elapsed &&
			path.m_end_time > aligned_elapsed)
		{
			core::vector2df pos = path.getPointByTime(aligned_elapsed);
			node->setPosition({ pos.X, 0.f, pos.Y });
			break;
		}
	}
}

scene::ISceneNodeAnimator* WalkAnimator::createClone(scene::ISceneNode* node, scene::ISceneManager* newManager)
{
	return new WalkAnimator(node, m_path);
}

bool WalkAnimator::hasFinished() const
{
	if (m_built_path.empty())
		true;

	uint32_t travel_interval = m_built_path[m_built_path.size() - 1].m_end_time;
	return (m_elapsed > travel_interval);
}

void WalkAnimator::buildPath()
{
	const float speed = 1.f;

	m_built_path.clear();
	m_built_path.reserve(m_path.size());

	if (m_path.size() == 0) return;

	for (unsigned i = 0; i < m_path.size() - 1; ++i)
	{
		Path p;

		p.m_start_point = m_path[i];
		p.m_end_point = m_path[i + 1];
		float dist = p.m_start_point.getDistanceFrom(p.m_end_point); // distance in units

		p.m_start_time = ((i == 0) ? 0 : (m_built_path[i - 1].m_end_time));
		p.m_end_time = p.m_start_time + (u32)((1000.f * dist) / speed); // x speed: x units / 1000 msec

		p.m_velocity = (p.m_start_point - p.m_end_point) / ((float)p.m_end_time - (float)p.m_start_time);

		m_built_path.push_back(p);
	}
}

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
