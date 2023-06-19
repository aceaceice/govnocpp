#include <fstream>
#include <iostream>
#include "utils.h"
#include "detection.h"
#include <string>

#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
std::string savedFilePath = "/home/jasos/Documents/saved.txt";
MousePosition getCursorPosition() {
    Display* display = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(display);
    XEvent event;
    XQueryPointer(display, root, &event.xbutton.root, &event.xbutton.window,
                  &event.xbutton.x_root, &event.xbutton.y_root,
                  &event.xbutton.x, &event.xbutton.y,
                  &event.xbutton.state);
    XCloseDisplay(display);
    MousePosition cursor;
    cursor.x = event.xbutton.x;
    cursor.y = event.xbutton.y;
    return cursor;
}

#elif __APPLE__
#include <ApplicationServices/ApplicationServices.h>
std::string savedFilePath = "/Users/jasos/Documents/saved.txt";
MousePosition getCursorPosition() {
    MousePosition cursor;
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursorPos = CGEventGetLocation(event);
    cursor.x = cursorPos.x;
    cursor.y = cursorPos.y;
    return cursor;
}

#endif

void writeToFile(const std::string& text, DetectedWords* recWordsPtr) {
    std::ofstream file(savedFilePath, std::ios::app); // Open the file in append mode

    if (file.is_open()) {
        file << text << std::endl; // Write the text to the file
        file.close();              // Close the file
        std::cout << "Text written to file successfully." << std::endl;
        // windowCloseCallback(window);
        recWordsPtr->clearSelected();
    } else {
        std::cout << "Error opening file." << std::endl;
    }
}
