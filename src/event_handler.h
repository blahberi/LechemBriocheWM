#ifndef _LBWM_EVENT_HANDLER
#define _LBWM_EVENT_HANDLER

#include "X11/Xlib.h"
#include <X11/X.h>

namespace lbwm {
    typedef void (*EventHandlerFunc)(XEvent*);

    class EventHandler {
        public:
            EventHandler(Display* display, EventHandlerFunc *handlers);

            void startEventLoop();
        private:
            Display* display;
            EventHandlerFunc handlers[LASTEvent];
    };
}

#endif // _LBWM_EVENT_HANDLER
