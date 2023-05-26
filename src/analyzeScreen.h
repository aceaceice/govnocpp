#ifndef ANALYZESCREEN_H
#define ANALYZESCREEN_H
#include <X11/Xlib.h>
#include "detection.h"

XEvent getMouseLocation();

DetectedWords analyzeScreen();
#endif