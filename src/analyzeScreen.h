#ifndef ANALYZESCREEN_H
#define ANALYZESCREEN_H
#include "detection.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

XEvent getMouseLocation();

DetectedWords analyzeScreen();
#endif