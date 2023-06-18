#ifndef ANALYZESCREEN_H
#define ANALYZESCREEN_H
#include "detection.h"

#ifdef __linux__ 
#include <X11/Xlib.h>
#include <X11/Xutil.h>

XEvent getMouseLocation();


#elif __APPLE__

#include <ApplicationServices/ApplicationServices.h>

CGPoint getMouseLocation();
#endif

DetectedWords analyzeScreen();
#endif