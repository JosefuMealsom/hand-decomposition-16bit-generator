#pragma once

enum class EventType {
  None = 0,
  WindowClose,
  WindowResize,
  KeyPressed,
  KeyReleased,
  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
};

// Note: a has inside a macro converts the variable to a string. Cool.
#define EVENT_CLASS_TYPE(type)                                                 \
  static EventType get_static_type() { return EventType::type; }               \
  virtual EventType get_event_type() const override {                          \
    return get_static_type();                                                  \
  }                                                                            \
  virtual const char *get_name() const override { return #type; }

class Event {
public:
  virtual const char *get_name() const = 0;
  virtual EventType get_event_type() const = 0;
};
