#ifndef UTILS_H
#define UTILS_H
#include <string>
#include "detection.h"
struct Cursor
{
    int x;
    int y;    /* data */
};

Cursor getCursorPosition();

void writeToFile(const std::string& text, DetectedWords* recWordsPtr);
#endif