#ifndef _LBWM_EVENT_HANDLER_BUILDER
#define _LBWM_EVENT_HANDLER_BUILDER
#include "event_handler.h"
namespace lbwm {
    class EventHandlerBuilder {
        public:
            EventHandlerBuilder();
            EventHandlerBuilder* setDisplay(Display* display);
            EventHandlerBuilder* setEventHandler(int event, EventHandlerFunc handler);
            EventHandler* build();
        private:
            Display* display;
            EventHandlerFunc handlers[LASTEvent];
    };
}
#endif // _LBWM_EVENT_HANDLER_BUILDER
