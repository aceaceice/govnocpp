#ifndef UTILS_H
#define UTILS_H
#include <string>
#include "detection.h"
struct MousePosition
{
    int x;
    int y;    /* data */
};

MousePosition getCursorPosition();

void writeToFile(const std::string& text, DetectedWords* recWordsPtr);
#endif