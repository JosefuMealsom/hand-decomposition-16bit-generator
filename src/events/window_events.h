#pragma once

#include "events/event.h"

class WindowResizeEvent : Event {
  EVENT_CLASS_TYPE(WindowResize)
};

class WindowCloseEvent : Event {
  EVENT_CLASS_TYPE(WindowClose)
};
