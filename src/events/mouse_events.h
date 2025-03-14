#pragma once

#include "events/event.h"

class MouseMovedEvent : Event {
  EVENT_CLASS_TYPE(MouseMoved)
};

class MouseButtonPressedEvent : Event {
  EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : Event {
  EVENT_CLASS_TYPE(MouseButtonReleased)
};
