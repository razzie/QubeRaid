/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <gg/event.hpp>
#include "inputs.hpp"

extern gg::IEventDefinition<KeyInput>& key_event;
extern gg::IEventDefinition<MouseInput>& mouse_event;
extern gg::IEventDefinition<GUIAction>& gui_event;
