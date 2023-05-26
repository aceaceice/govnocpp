#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H
#include <X11/Xlib.h>
#include <string>
#include <leptonica/allheaders.h>

void saveXImageAsPNG(XImage* ximage, const std::string& filename);

void savePixToFile(Pix* pix, const std::string& filename) ;

Pix* ximageToPix(XImage* ximage);

Pix* takeScreenshot();
#endif