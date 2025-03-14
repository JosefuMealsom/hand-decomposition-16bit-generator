#pragma once

#include "events/event.h"
#include "events/key_code.h"

class KeyPressedEvent : public Event {

public:
  KeyPressedEvent(const KeyCode key_code) {}
  EVENT_CLASS_TYPE(KeyPressed);
};

class KeyReleasedEvent : public Event {

public:
  KeyReleasedEvent(const KeyCode key_code) {}
  EVENT_CLASS_TYPE(KeyReleased);
};
