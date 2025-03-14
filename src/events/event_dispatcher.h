#include "events/event.h"

class EventDispatcher {
public:
  EventDispatcher(Event &event) : m_event(event){};

  // How this works is that we create a dispatcher linked to
  // a certain event. If the type of the event is the same, then the function
  // template param, F, gets called.
  template <typename E, typename F> bool dispatch(const F &func) {
    if (m_event.get_event_type() == E::get_static_type()) {
      func(m_event);
      return true;
    }

    return false;
  }

private:
  const Event &m_event;
};
