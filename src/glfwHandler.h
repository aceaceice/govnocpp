#ifndef GLFW_HANDLER_H
#define GLFW_HANDLER_H
#include <GLFW/glfw3.h>
#include "detection.h"
#include <string>

void drawBoundingBox(int x1, int y1, int x2, int y2) ;


typedef struct {DetectedWords* recWords;} RecognizedWordData;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
int run_detection();
void errorCallback(int error, const char* description);
#endif