#include "event_handler.h"
#include <X11/X.h>
#include <algorithm>
using namespace lbwm;

EventHandler::EventHandler(EventHandlerFunc *handlers)
{
    std::copy(handlers, handlers + LASTEvent, this->handlers);
}
