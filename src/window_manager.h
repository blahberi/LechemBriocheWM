#include "x_event_handler.h"
#include <X11/Xlib.h>

namespace lbwm {
    class WindowManager{
        public:
            // Singleton
            static WindowManager& getInstance();
            WindowManager(const WindowManager&) = delete; // Disable copy constructor
            WindowManager& operator=(const WindowManager&) = delete;

            bool initialize();
        private:
            WindowManager(); // Hide constructor
            ~WindowManager(); // Hide destructor

            Display *display;
            XErrorHandler DefaultErrorHandler;
            bool _isOtherWmRunning;

            bool isOtherWmRunning();
            static int OnOtherWmRunningError(Display* display, XErrorEvent* error);
            static int OnXError(Display* display, XErrorEvent* error);
    };
}
