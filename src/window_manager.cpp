#include "window_manager.h"
#include <X11/Xlib.h>
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
    this->DefaultErrorHandler = XSetErrorHandler(OnOtherWmRunningError);
    XSync(this->display, false);
    if (this->_isOtherWmRunning) return true;
    return false;
}

int WindowManager::OnXError(Display* display, XErrorEvent* error) {
    return getInstance().DefaultErrorHandler(display, error);
}

int WindowManager::OnOtherWmRunningError(Display* display, XErrorEvent* error) {
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
    XSetErrorHandler(OnXError);

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

    return true;
}
