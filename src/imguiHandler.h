#ifndef IMGUI_HANDLER_H
#define IMGUI_HANDLER_H
#include "imgui.h"
#include "detection.h"

void renderImGuiWindow(ImFont* font, DetectedWords* recWordsPtr);
#endif