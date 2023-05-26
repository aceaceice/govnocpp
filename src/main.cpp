// #include <tesseract/baseapi.h>
// #include <fstream>
// #include <iostream>
// #include <leptonica/allheaders.h>
// #include <GLFW/glfw3.h>
// #include "screenCapture.h"
// #include "detection.h"
// #include "analyzeScreen.h"






// void drawBoundingBox(int x1, int y1, int x2, int y2) {
//     // Set up the projection matrix to use pixel coordinates
//     glMatrixMode(GL_PROJECTION);
//     glPushMatrix();
//     glLoadIdentity();
//     glOrtho(0, 2560, 1440, 0, -1, 1); // Replace with your window size
    
//     // Set up the modelview matrix to draw in 2D
//     glMatrixMode(GL_MODELVIEW);
//     glPushMatrix();
//     glLoadIdentity();
    
//     // Calculate the correct width and height based on the given coordinates
//     int width = abs(x2 - x1);
//     int height = abs(y2 - y1);
    
//     // Determine the starting point for drawing the rectangle
//     int startX = std::min(x1, x2);
//     int startY = std::min(y1, y2);
    
//     // Draw the bounding box
//     glColor3f(1.0f, 0.0f, 0.0f); // Red color
//     glBegin(GL_LINE_LOOP);
//     glVertex2i(x1, y1);
//     glVertex2i(x1, y2);
//     glVertex2i(x2, y2);
//     glVertex2i(x2, y1);
//     glEnd();
    
//     // Restore the projection and modelview matrices
//     glPopMatrix();
//     glMatrixMode(GL_PROJECTION);
//     glPopMatrix();
//     glMatrixMode(GL_MODELVIEW);
// }


// typedef struct {DetectedWords* recWords;} RecognizedWordData;



// // Function to handle keyboard events
// void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
//     RecognizedWordData* recWordsData = static_cast<RecognizedWordData*>(glfwGetWindowUserPointer(window));
//     DetectedWords* recWordsPtr = recWordsData->recWords;
//     DetectedWords& recWords = *recWordsPtr;
//     // RecognizedWordData* recWordsData = (RecognizedWordData*)glfwGetWindowUserPointer(window);
//     // DetectedWords recWords = recWordsData->recWords;
//     std::cout<< &recWords << " WASDSZXGXCB______________-" << std::endl;

//     if (action == GLFW_PRESS) {
//         switch(key) {
//             case GLFW_KEY_R: {
//                 glfwMakeContextCurrent(window);

//                 XEvent event = getMouseLocation();  
//                 int initialWordId = recWords.findMatchingWord(event.xbutton.x, event.xbutton.y);
//                 // recWords.selectWord(initialWordId);
//                 Coordinates initialWord = recWords.getBoundingBox(initialWordId);
//                 // std::cout << initialWord.position.x1 << "  " << initialWord.position.x2 << std::endl;
//                 // drawBoundingBox(initialWord.position.x1, initialWord.position.y1, initialWord.position.x2, initialWord.position.y2);
//                 glfwSwapBuffers(window);

//             }
//             break;
//             case GLFW_KEY_Q: {
//                 glfwMakeContextCurrent(window);
//                 std::cout<<"TES" << std::endl;
            
//                 RecognizedWord prevWord = recWords.selectPrev();
//                 std::cout << prevWord.position.x1 << "  " << prevWord.position.x2 << std::endl;
//                 drawBoundingBox(prevWord.position.x1, prevWord.position.y1, prevWord.position.x2, prevWord.position.y2);
//                 glfwSwapBuffers(window);
            
//             }
//             break;
//             case GLFW_KEY_SPACE: { 
//                 std::cout << &recWords << std::endl;
//                 // Draw a square at a specific position on the screen
//                 int xStart = 100;
//                 int yStart = 100;
//                 int xEnd = 200;
//                 int yEnd = 200;
//                 // Make the OpenGL context of the window current
//                 glfwMakeContextCurrent(window);

//                 // Draw your scene here
//                 drawBoundingBox(xStart, yStart, xEnd, yEnd);

//                 // Swap front and back buffers
//                 glfwSwapBuffers(window);
//                     }
//             break;
//             case GLFW_KEY_D: {
//                 int xStart = 150;
//                 int yStart = 150;
//                 int xEnd = 300;
//                 int yEnd = 300;

//                 // Make the OpenGL context of the window current
//                 glfwMakeContextCurrent(window);

//                 // Draw your scene here
//                 drawBoundingBox(xStart, yStart, xEnd, yEnd);

//                 // Swap front and back buffers
//                 glfwSwapBuffers(window);
//             }
//             break;
//         }
        
//     }
// }

// int main()
// {
//     DetectedWords recWords = analyzeScreen();
//     RecognizedWordData recWordsData;
//     recWordsData.recWords = &recWords; 
//     // Initialize GLFW
//     if (!glfwInit())
//         return -1;

//     glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
//     glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
//     // Retrieve the primary monitor
//     GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();



//     // Create a GLFW window
//     // GLFWwindow* window = glfwCreateWindow(2560, 1440, "Keyboard Events", NULL, NULL);
//     const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

//     GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "Fullscreen Window", primaryMonitor, NULL);
//     glfwSetWindowUserPointer(window, &recWordsData);
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

//     if (!window)
//     {
//         glfwTerminate();
//         return -1;
//     }
//     // Set the keyboard callback function
//     glfwSetKeyCallback(window, keyCallback);

//     // Make the OpenGL context of the window current
//     glfwMakeContextCurrent(window);

//     // Loop until the user closes the window
//     while (!glfwWindowShouldClose(window))
//     {
//         // Poll for and process events
//         glfwPollEvents();
//     }

//     // Terminate GLFW
//     glfwTerminate();

//     return 0;
// }

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <fstream>
Display* display = XOpenDisplay(nullptr);
Window root = DefaultRootWindow(display);
XWindowAttributes attributes;
XGetWindowAttributes(display, root, &attributes);
int width = attributes.width;
int height = attributes.height;
XImage* image = XGetImage(display, root, 0, 0, width, height, AllPlanes, ZPixmap);
std::string filename = "screenshot.ppm";
FILE* file = fopen(filename.c_str(), "wb");
if (file != nullptr) {
    fprintf(file, "P6\n%d %d\n255\n", width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned long pixel = XGetPixel(image, x, y);
            unsigned char r = (pixel & image->red_mask) >> 16;
            unsigned char g = (pixel & image->green_mask) >> 8;
            unsigned char b = pixel & image->blue_mask;
            fputc(r, file);
            fputc(g, file);
            fputc(b, file);
        }
    }
    fclose(file);
}
XDestroyImage(image);
XCloseDisplay(display);
