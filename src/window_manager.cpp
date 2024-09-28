#include "window_manager.h"
#include "event_handler_builder.h"
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <csignal>
#include <iostream>
#include <wait.h>
using lbwm::WindowManager;

WindowManager& WindowManager::getInstance() {
    static WindowManager instance;
    return instance;
}

bool WindowManager::isOtherWmRunning() {
    _isOtherWmRunning = false;
    this->DefaultErrorHandler = XSetErrorHandler(onOtherWmRunningError);
    XSync(this->display, false);
    if (this->_isOtherWmRunning) return true;
    return false;
}

int WindowManager::onXError(Display* display, XErrorEvent* error) {
    return getInstance().DefaultErrorHandler(display, error);
}

int WindowManager::onOtherWmRunningError(Display* display, XErrorEvent* error) {
    WindowManager& instance = getInstance();
    getInstance()._isOtherWmRunning = true;
    return -1;
}

bool WindowManager::initialize() {
    // Connect to the X server, the connection is returned and stored in "display"
    this->display = XOpenDisplay(NULL);
    // If the connection is rejected, XOpenDisplay returns a null pointer
    if (this->display == nullptr) {
        std::cerr << "Couldn't connect to X server" << std::endl;
        return false;
    }
    if(this->isOtherWmRunning()) {
        std::cerr << 
            "Couldn't run because another windoow manager is already "
            "running: " << XDisplayString(this->display)<< std::endl;
        return false;
    }
    XSetErrorHandler(onXError);

    /* If a child terminates, it becomes a "zombie" until the parent process 
     * reads its exit status. While zombie processes don't consume resources, 
     * they still require a PID. By telling the OS to ignore the SIGCHLD signal 
     * (the signal that is received when a child process stops or terminates), 
     * the OS won't turn the process into a zombie. We do this with the signal
     * method and the SIG_IGN (ignore) handler. It tells the OS to handle this 
     * signal using the custom handler. To clean all current zombies, we just 
     * have to read their exit status. We loop over all such child processes 
     * and read their status with waitpid */
    signal(SIGCHLD, SIG_IGN);
    while (waitpid(-1, NULL, WNOHANG));

    this->defaultScreen = DefaultScreen(this->display);
    this->rootWindow = RootWindow(this->display, this->defaultScreen);


    initEventHandler();
    return true;
}

void WindowManager::initEventHandler() {
    long eventMask =
        SubstructureRedirectMask|
        SubstructureNotifyMask|
        ButtonPressMask|
        PointerMotionMask|
        EnterWindowMask|
        LeaveWindowMask|
        StructureNotifyMask|
        PropertyChangeMask;

    EventHandlerBuilder* eventHandlerBuilder = new EventHandlerBuilder();
    eventHandlerBuilder
        ->setEventHandler()
        ->setEventHandler();

}

void WindowManager::initAtoms() {
    // Get window manager related atoms' identifiers
    this->wmAtoms[WMAtoms_Protocols] = XInternAtom(this->display, "WM_PROTOCOLS", false);
    this->wmAtoms[WMAtoms_DeleteWindow] = XInternAtom(this->display, "WM_DELETE_WINDOW", false);
    this->wmAtoms[WMAtoms_State] = XInternAtom(this->display, "WM_STATE", false);
    this->wmAtoms[WMAtoms_TakeFocus] = XInternAtom(this->display, "WM_TAKE_FOCUS", false);

    // Get net atoms' identifiers
    this->netAtoms[NetAtoms_ActiveWindow] = XInternAtom(this->display, "_NET_ACTIVE_WINDOW", false);
    this->netAtoms[NetAtoms_Supported] = XInternAtom(this->display, "_NET_SUPPORTED", false);
    this->netAtoms[NetAtoms_WmName] = XInternAtom(this->display, "_NET_WM_NAME", false);
    this->netAtoms[NetAtoms_WmState] = XInternAtom(this->display, "_NET_WM_STATE", false);
    this->netAtoms[NetAtoms_SupportingWmCheck] = XInternAtom(this->display, "_NET_SUPPORTING_WM_CHECK", false);
    this->netAtoms[NetAtoms_WmStateFullscreen] = XInternAtom(this->display, "_NET_WM_STATE_FULLSCREEN", false);
    this->netAtoms[NetAtoms_WmWindowType] = XInternAtom(this->display, "_NET_WM_WINDOW_TYPE", false);
    this->netAtoms[NetAtoms_WmWindowTypeDialog] = XInternAtom(this->display, "_NET_WM_WINDOW_TYPE_DIALOG", false);
    this->netAtoms[NetAtoms_ClientList] = XInternAtom(this->display, "_NET_CLIENT_LIST", false);
}

void WindowManager::createSupportWindow() {
    // Atom identifier for string type values
    Atom utf8string = XInternAtom(this->display, "UTF8_STRING", false);

    this->wmSupportingWindow = XCreateSimpleWindow(
            this->display,
            this->rootWindow, // parent
            0, 0, 1, 1, //x, y, width, height
            0, 0, 0 // border width, border, background
    );
    XChangeProperty(
            this->display,
            this->wmSupportingWindow,
            this->netAtoms[NetAtoms_SupportingWmCheck],
            XA_WINDOW, 32,
            PropModeReplace,
            (unsigned char *) &this->wmSupportingWindow, 1
    );
    XChangeProperty(
            this->display,
            this->wmSupportingWindow,
            this->netAtoms[NetAtoms_WmName],
            utf8string, 8,
            PropModeReplace,
            (unsigned char *) "lbwm", 4
    );
    XChangeProperty(
            this->display,
            this->rootWindow,
            this->netAtoms[NetAtoms_SupportingWmCheck],
            XA_WINDOW, 32,
            PropModeReplace,
            (unsigned char *) &this->wmSupportingWindow, 1
    );
    XChangeProperty(
            this->display,
            this->rootWindow,
            this->netAtoms[NetAtoms_Supported],
            XA_ATOM, 32,
            PropModeReplace,
            (unsigned char *) this->netAtoms, 
            NetAtoms_COUNT
    );
    XDeleteProperty(
            this->display,
            this->rootWindow,
            this->netAtoms[NetAtoms_ClientList]
    );
}
