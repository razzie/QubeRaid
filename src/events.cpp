/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <gg/thread.hpp>
#include "events.hpp"

const gg::IEvent::Type INTERNAL_EVENTS_BASE = 0;
const gg::IEvent::Type BACKEND_EVENTS_BASE = 100;
const gg::IEvent::Type NETWORK_EVENTS_BASE = 200;
const gg::IEvent::Type UI_EVENTS_BASE = 300;


static gg::LocalEventDefinition<UI_EVENTS_BASE + 1, KeyInput> s_key_event;
gg::IEventDefinition<KeyInput>& key_event = s_key_event;

static gg::LocalEventDefinition<UI_EVENTS_BASE + 2, MouseInput> s_mouse_event;
gg::IEventDefinition<MouseInput>& mouse_event = s_mouse_event;

static gg::LocalEventDefinition<UI_EVENTS_BASE + 3, GUIAction> s_gui_event;
gg::IEventDefinition<GUIAction>& gui_event = s_gui_event;
