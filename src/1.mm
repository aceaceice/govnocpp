#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <ApplicationServices/ApplicationServices.h>
#import <AppKit/AppKit.h>

// function to launch program
void launchProgram() {
    std::cout << "Launching program..." << std::endl;
    system("./build/debug/play");
}

bool stopFlag = false;

void signalHandler(int signal) {
    if (signal == SIGINT) {
        std::cout << "Stopping..." << std::endl;
        stopFlag = true;
    }
}

// callback function for key events
CGEventRef keyEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon) {
    NSEvent* nsEvent = [NSEvent eventWithCGEvent:event];
    
    // Check if the event is a key down event
    if (type == kCGEventKeyDown) {
        if ([nsEvent modifierFlags] & NSEventModifierFlagCommand) {
            std::cout << "Command pressed" << nsEvent << std::endl;
        }
         if ([nsEvent modifierFlags] & NSEventModifierFlagShift){
            std::cout << "Shift pressed" << nsEvent << std::endl;
        }
         if ([[nsEvent charactersIgnoringModifiers] isEqualToString:@"K"]) {
            std::cout << "K pressed" << nsEvent << std::endl;
        }
        // Check if the command+shift+k combination was pressed
        if (([nsEvent modifierFlags] & NSEventModifierFlagCommand) &&
            ([nsEvent modifierFlags] & NSEventModifierFlagShift) &&
            [[nsEvent charactersIgnoringModifiers] isEqualToString:@"K"]) {
            // Launch the program
            launchProgram();
        }
    }
    
    // Log the event type and key code
    
    // Return the event
    return event;
}

int main(int argc, char* argv[]) {
    std::cout << "Press Ctrl-Shift-C to launch program." << std::endl;

    // set up signal handler
    signal(SIGINT, signalHandler);

    // create event tap for key events
    CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionListenOnly,
                                              kCGEventMaskForAllEvents, keyEventCallback, NULL);
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);

    // enable event tap
    CGEventTapEnable(eventTap, true);

    // run event loop
    while (!stopFlag) {
        CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.1, false);
    }

    // disable event tap
    CGEventTapEnable(eventTap, false);

    // release resources
    CFRelease(eventTap);
    CFRelease(runLoopSource);

    return 0;
}
