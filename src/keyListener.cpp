// Filename: objcWrapper.mm


//  // // // // // // // // // // //template <typename T>
#include "glfwHandler.h"
#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XInput2.h>
#include <iostream>

void startKeyListener() {
    // Open the display connection
    Display* display = XOpenDisplay(nullptr);

    // Variables for XInput extension
    int xi_opcode, event, error;

    // Check if XInput extension is available
    if (!XQueryExtension(display, "XInputExtension", &xi_opcode, &event, &error)) {
        // XInput extension not available
        // Handle the error or exit the program
        std::cout << "No" << std::endl;  
    }

    // Get the root window of the display
    Window rootWindow = DefaultRootWindow(display);

    // Set up event mask to select keyboard events
    XIEventMask evmask{};
    unsigned char mask[(XI_LASTEVENT + 7)/8] = { 0 };
    evmask.deviceid = XIAllDevices;
    evmask.mask_len = sizeof(mask);
    evmask.mask = mask;
    XISetMask(mask, XI_KeyPress);

    // Select the events to capture using XInput2
    XISelectEvents(display, rootWindow, &evmask, 1);

    // Event capture loop
while (true) {
    // Get the next event from the event queue
    XEvent xevent;
    XNextEvent(display, &xevent);

    // Check if it's an XInput event
    if (xevent.xcookie.type == GenericEvent && xevent.xcookie.extension == xi_opcode) {
        // Retrieve the XInput event data
        XGetEventData(display, &xevent.xcookie);
        XGenericEventCookie* cookie = &xevent.xcookie;

        // Check if it's a keyboard event
        if (cookie->evtype == XI_KeyPress) {
            // Retrieve the keyboard event data
            XIDeviceEvent* xievent = reinterpret_cast<XIDeviceEvent*>(cookie->data);
            int keycode = xievent->detail;

            // Check for the specific key combination
            KeyCode ctrlKeyCode = XKeysymToKeycode(display, XK_Control_L);
            KeyCode fKeyCode = XKeysymToKeycode(display, XK_f);

            if (keycode == fKeyCode &&  (xievent->mods.effective & ControlMask)) {
                // Key combination Ctrl+. is pressed
                // Handle the specific key combination here
                std::cout << "Ctrl+. is pressed" << std::endl;
                run_detection();
            }
            // Free the event data
            XFreeEventData(display, &xevent.xcookie);
        }
    }
}


    // Close the display connection
    XCloseDisplay(display);
}

#elif __APPLE__

#include <thread>
#import <Cocoa/Cocoa.h>
#include "keyListener.h"
#include <iostream>


void startKeyListener() {
__block BOOL shouldIgnoreKeyEvents = NO;
    @autoreleasepool {
        NSApplication* app = [NSApplication sharedApplication];
    run_detection();

        NSEventMask eventMask = NSEventMaskKeyDown;
        [NSEvent addGlobalMonitorForEventsMatchingMask:eventMask handler:^(NSEvent* event) {
            if (shouldIgnoreKeyEvents) return;
                std::cout << "Ctrl + F is pressed" << std::endl;

            if (([event modifierFlags] & NSEventModifierFlagControl) && [event keyCode] == 0x03) {  // 0x03 is 'F' key
                std::cout << "Ctrl + F is pressed" << std::endl;
                shouldIgnoreKeyEvents = YES;
                run_detection();
                shouldIgnoreKeyEvents = NO;
            }
        }];

        [app run];
    }
}


#endif
