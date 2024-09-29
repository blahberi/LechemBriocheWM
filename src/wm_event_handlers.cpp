#include "window_manager.h"
#include <iostream>
using namespace lbwm;
using namespace std;

void WindowManager::onButtonPress(XEvent* event) {
    cout << "button press" << endl;
}

void WindowManager::onClientMessage(XEvent* event) {
    cout << "client message" << endl;
}

void WindowManager::onConfigureRequest(XEvent* event) {
    cout << "configure request" << endl;
}

void WindowManager::onConfigureNotify(XEvent* event) {
    cout << "configure notify" << endl;
}

void WindowManager::onDestroyNotify(XEvent* event) {
    cout << "destroy notify" << endl;
}

void WindowManager::onEnterNotify(XEvent* event) {
    cout << "enter notify" << endl;
}

void WindowManager::onExpose(XEvent* event) {
    cout << "expose" << endl;
}

void WindowManager::onFocusIn(XEvent* event) {
    cout << "focus in" << endl;
}

void WindowManager::onKeypress(XEvent* event) {
    cout << "keypress" << endl;
}

void WindowManager::onUnmapNotify(XEvent* event) {
    cout << "unmap notify" << endl;
}

void WindowManager::onMappingNotify(XEvent* event) {
    cout << "mapping notify" << endl;
}

void WindowManager::onMapRequest(XEvent* event) {
    cout << "onMapRequest" << endl;
}

void WindowManager::onMotionNotify(XEvent* event) {
    cout << "motion notify" << endl;
}

void WindowManager::onPropertyNotify(XEvent* event) {
    cout << "property notify" << endl;
}

