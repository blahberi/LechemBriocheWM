#include "event_handler_builder.h"
using namespace lbwm;

EventHandlerBuilder::EventHandlerBuilder() :
    handlers{nullptr}
{}

EventHandlerBuilder* EventHandlerBuilder::setEventHandler(
        int event,
        EventHandlerFunc handler
    )
{
    this->handlers[event] = handler;
    return this;
}

EventHandler* EventHandlerBuilder::build() {
    return new EventHandler(this->handlers);
}
