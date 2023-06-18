#include <thread>
#import <Cocoa/Cocoa.h>
#include <iostream>


int main() {
__block BOOL shouldIgnoreKeyEvents = NO;
    @autoreleasepool {
        NSApplication* app = [NSApplication sharedApplication];

        NSEventMask eventMask = NSEventMaskKeyDown;
        [NSEvent addGlobalMonitorForEventsMatchingMask:eventMask handler:^(NSEvent* event) {
            if (shouldIgnoreKeyEvents) return;

            if (([event modifierFlags] & NSEventModifierFlagCommand) && [event keyCode] == 0x05) {  // 0x03 is 'F' key
                std::cout << "Ctrl + F is pressed" << std::endl;
            system("./build/debug/play");
            }
        }];

        [app run];
    }
    return 0;
}