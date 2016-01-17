/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "events/inputevents.hpp"

using namespace gg::literals;


static gg::LocalEventDefinition<"key"_event, KeyInput> s_key_event;
gg::IEventDefinition<KeyInput>& key_event = s_key_event;

static gg::LocalEventDefinition<"mouse"_event, MouseInput> s_mouse_event;
gg::IEventDefinition<MouseInput>& mouse_event = s_mouse_event;

static gg::LocalEventDefinition<"gui"_event, GUIAction> s_gui_event;
gg::IEventDefinition<GUIAction>& gui_event = s_gui_event;
