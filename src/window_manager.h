#ifndef _LBWM_WINDOW_MANAGER
#define _LBWM_WINDOW_MANAGER

#include "event_handler.h"
#include "atoms.h"
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
            int defaultScreen;
            Window rootWindow;
            Window wmSupportingWindow;
            Atom wmAtoms[WMAtoms_COUNT];
            Atom netAtoms[NetAtoms_COUNT];
            XErrorHandler DefaultErrorHandler;
            bool _isOtherWmRunning;

            EventHandler* eventHandler;

            bool isOtherWmRunning();
            void initAtoms();
            void createSupportWindow();
            void initEventHandler();
            static int onOtherWmRunningError(Display* display, XErrorEvent* error);
            static int onXError(Display* display, XErrorEvent* error);

            // Event handlers
            static void onButtonPress(XEvent* event);
            static void onClientMessage(XEvent* event);
            static void onConfigureRequest(XEvent* event);
            static void onConfigureNotify(XEvent* event);
            static void onDestroyNotify(XEvent* event);
            static void onEnterNotify(XEvent* event);
            static void onExpose(XEvent* event);
            static void onFocusIn(XEvent* event);
            static void onKeypress(XEvent* event);
            static void onUnmapNotify(XEvent* event);
            static void onMappingNotify(XEvent* event);
            static void onMapRequest(XEvent* event);
            static void onMotionNotify(XEvent* event);
            static void onPropertyNotify(XEvent* event);
    };
}

#endif // _LBWM_WINDOW_MANAGER
