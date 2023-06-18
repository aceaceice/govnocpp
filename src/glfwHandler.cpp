#include <GL/glew.h>
#include <iostream>
#include "glfwHandler.h"
#include  "imguiHandler.h"
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "detection.h"
#include "utils.h"
#include "analyzeScreen.h"
std::string translationText = "";
bool shouldExit = false;
DetectedWords* recWordsPtr;

// Function to handle keyboard events
void drawBoundingBox(int x1, int y1, int x2, int y2) {
    // Set up the projection matrix to use pixel coordinates
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 2560, 1440, 0, -1, 1); // Replace with your window size
    
    // Set up the modelview matrix to draw in 2D
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Draw the bounding box
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glEnd();
    
    // Restore the projection and modelview matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}



void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    RecognizedWordData* recWordsData = static_cast<RecognizedWordData*>(glfwGetWindowUserPointer(window));
    DetectedWords* recWordsPtr = recWordsData->recWords;
    DetectedWords& recWords = *recWordsPtr;

    if (action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_SEMICOLON: {
                MousePosition cursor = getCursorPosition();  
                try {
                recWords.findMatchingWord(cursor.x, cursor.y);
                } catch (const std::exception& e) {
                    // std::cout << e.what() << std::endl;
                }
            }

            break;
            case GLFW_KEY_LEFT_BRACKET: {
                recWords.selectPrev();            
            }
            break;
            case GLFW_KEY_RIGHT_BRACKET: { 
                recWords.selectNext();
            }
            break;
            case GLFW_KEY_ENTER: {
                recWords.translateSelected();
            }
            break;
        }
        
    }
}

void errorCallback(int error, const char* description)
{
    printf("GLFW Error %d: %s\n", error, description);
}

// Set the error callback
int run_detection() { 
    
    shouldExit = false;

    DetectedWords recWords = analyzeScreen();
    recWordsPtr = &recWords;
    recWords.shouldExit = false;
    recWords.detectionError = "";
    RecognizedWordData recWordsData;
    recWordsData.recWords = &recWords; 
    // Initialize GLFW
    if (!glfwInit())
        return -1;
glfwSetErrorCallback(errorCallback);
    
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    // Retrieve the primary monitor
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

    

    // Create a GLFW window
    // GLFWwindow* window = glfwCreateWindow(2560, 1440, "Keyboard Events", NULL, NULL);
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    std::cout << videoMode->width << " " << videoMode->height << std::endl;
    std::cout << primaryMonitor << std::endl;
    GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "Fullscreen Window", primaryMonitor, NULL);
    std::cout << "GLFW window created" << std::endl;
    std::cout << window << std::endl;
    if(!window){
        std::cout << "Failed to create GLFW window" << std::endl;
    }
    glfwSetWindowUserPointer(window, &recWordsData);
    std::cout << "GLFW window created" << std::endl;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    std::cout << videoMode->width << " " << videoMode->height << std::endl;
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
     glfwSetKeyCallback(window, keyCallback);
    // Make the OpenGL context of the window current
    glfwMakeContextCurrent(window);
    std::cout << "GLFW initialized" << std::endl;
    glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    // const char* fontPath = "/System/Library/Fonts/Supplemental/Arial.ttf";
    const char* fontPath = "/usr/share/fonts/TTF/DejaVuSans.ttf";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImFont* font = io.Fonts->AddFontFromFileTTF(fontPath, 18.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
if (font == NULL) {
    // Handle error
    std::cout << "Failed to load font" << std::endl;
    return -1;
}
     ImGui::StyleColorsDark();
    // Setup Platform/Renderer bindings

 ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 120");

    // Set the keyboard callback function
   
    // Loop until the user closes the window
    // Loop until the user closes the window
while (!glfwWindowShouldClose(window) && !recWords.shouldExit) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the frame
    for(int i = 0; i < recWords.selectedWords.size(); i++){
    // std::cout<< recWords.selectedWords[0].position.x1 << "  " << recWords.selectedWords[0].position.y1 << " " << recWords.selectedWords[0].position.x2 << " " << recWords.selectedWords[0].position.y2 << std::endl;
        int x1 = recWords.selectedWords[i].position.x1;
        int y1 = recWords.selectedWords[i].position.y1;
        int x2 = recWords.selectedWords[i].position.x2;
        int y2 = recWords.selectedWords[i].position.y2;
        drawBoundingBox(x1, y1, x2, y2);
        // drawBoundingBox(recWords.selectedWords[i].position.x1, recWords.selectedWords[i].position.y1, recWords.selectedWords[i].position.x2, recWords.selectedWords[i].position.y2);
    }
        renderImGuiWindow(font, recWordsPtr);
        // Swap front and back buffers
        glfwSwapBuffers(window);
    // Poll for and process events
    glfwPollEvents();
    // Check if the window should be closed

    // Your other rendering and logic code here
}
 ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
// Terminate GLFW
glfwTerminate();
    return 0;
}
