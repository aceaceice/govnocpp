#include <ApplicationServices/ApplicationServices.h>
#include <fstream>
#include <iostream>
#include "utils.h"
#include "detection.h"
#include <string>


Cursor getCursorPosition() {
    Cursor cursor;
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursorPos = CGEventGetLocation(event);
    cursor.x = cursorPos.x;
    cursor.y = cursorPos.y;
    return cursor;
}

void writeToFile(const std::string& text, DetectedWords* recWordsPtr) {
    std::ofstream file("saved.txt", std::ios::app); // Open the file in append mode

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
