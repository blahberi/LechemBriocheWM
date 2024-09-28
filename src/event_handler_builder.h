#ifndef _LBWM_EVENT_HANDLER_BUILDER
#define _LBWM_EVENT_HANDLER_BUILDER
#include "event_handler.h"
#include <X11/X.h>

namespace lbwm {
    class EventHandlerBuilder {
        public:
            EventHandlerBuilder();
            EventHandlerBuilder* setEventHandler(int event, EventHandlerFunc handler);
            EventHandler* build();
        private:
            EventHandlerFunc handlers[LASTEvent];
    };
}
#endif // _LBWM_EVENT_HANDLER_BUILDER
