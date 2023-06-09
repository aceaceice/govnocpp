#include <tesseract/baseapi.h>
#include <fstream>
#include <iostream>
#include <leptonica/allheaders.h>
#include <GL/glew.h>
#include <string>

#include <GLFW/glfw3.h>
#include "screenCapture.h"
#include "detection.h"
#include "analyzeScreen.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XInput2.h>
// #include <X11/extensions/XInput.h> // Include XInput extension header
#include <typeinfo>


std::string translationText = "sda - блять";
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


typedef struct {DetectedWords* recWords;} RecognizedWordData;


struct DialogData {
    const char* text;
    GLFWwindow* window;
};
bool shouldExit = false;
void windowCloseCallback(GLFWwindow* window){
    std::cout << "asdasdasdasdas 12312 " << std::endl;
    std::cout << window << "Shit loop" << std::endl;
            glfwSetWindowShouldClose(window, GLFW_TRUE);


}

void writeToFile(const std::string& text) {
    std::ofstream file("saved.txt", std::ios::app); // Open the file in append mode

    if (file.is_open()) {
        file << text << std::endl; // Write the text to the file
        file.close();              // Close the file
        std::cout << "Text written to file successfully." << std::endl;
        // windowCloseCallback(window);
        shouldExit = true;
    } else {
        std::cout << "Error opening file." << std::endl;
    }
}

void exitLoop(){
            shouldExit = true;

}

bool renderFlag = false;

void renderImGuiWindow(ImFont* font)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::PushFont(font);
    ImGui::Begin("ImGui Window"); 

    ImGui::Text(translationText.c_str());

    if (ImGui::Button("Save"))                         
    {
        writeToFile(translationText);
    }

    if (ImGui::Button("Exit"))                         
    {
        shouldExit = true;
    }

    // Additional actions when 'D' is pressed
    if (renderFlag)
    {
        // Execute additional rendering tasks here

        renderFlag = false;  // Reset the flag
    }

    ImGui::End();
    ImGui::PopFont();
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Function to handle keyboard events
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    RecognizedWordData* recWordsData = static_cast<RecognizedWordData*>(glfwGetWindowUserPointer(window));
    DetectedWords* recWordsPtr = recWordsData->recWords;
    DetectedWords& recWords = *recWordsPtr;
    // RecognizedWordData* recWordsData = (RecognizedWordData*)glfwGetWindowUserPointer(window);
    // DetectedWords recWords = recWordsData->recWords;
    std::cout<< &recWords << " WASDSZXGXCB______________-" << std::endl;

    if (action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_R: {
                glfwMakeContextCurrent(window);

                XEvent event = getMouseLocation();  
                RecognizedWord initialWord = recWords.findMatchingWord(event.xbutton.x, event.xbutton.y);
                // recWords.selectWord(initialWordId);
                // Coordinates initialWord = recWords.getBoundingBox(initialWordId);
                // std::cout << initialWord.position.x1 << "  " << initialWord.position.x2 << std::endl;
                drawBoundingBox(initialWord.position.x1, initialWord.position.y1, initialWord.position.x2, initialWord.position.y2);
                glfwSwapBuffers(window);

            }
            break;
            case GLFW_KEY_Q: {
                glfwMakeContextCurrent(window);
                std::cout<<"TES" << std::endl;
            
                RecognizedWord prevWord = recWords.selectPrev();
                std::cout << prevWord.position.x1 << "  " << prevWord.position.x2 << "y dim" << prevWord.position.y1 << "  " << prevWord.position.y2<< std::endl;
                drawBoundingBox(prevWord.position.x1, prevWord.position.y1, prevWord.position.x2, prevWord.position.y2);
                glfwSwapBuffers(window);
            
            }
            break;
            case GLFW_KEY_E: {
                glfwMakeContextCurrent(window);
                std::cout<<"TES" << std::endl;
            
                RecognizedWord nextWord = recWords.selectNext();
                // std::cout << prevWord.position.x1 << "  " << prevWord.position.x2 << "y dim" << prevWord.position.y1 << "  " << prevWord.position.y2<< std::endl;
                drawBoundingBox(nextWord.position.x1, nextWord.position.y1, nextWord.position.x2, nextWord.position.y2);
                glfwSwapBuffers(window);
            
            }
            break;
            case GLFW_KEY_T: {
                 glfwMakeContextCurrent(window);

                // Draw your scene here
                std::string translation = recWords.translateSelected();
                // recWords.translationText = translation.c_str();
                translationText = translation;
                // std::cout << recWords.translationText << std::endl;
                // show_dialog(cTranslation, window);

    // Start the main GTK+ loop

                // Swap front and back buffers
                glfwSwapBuffers(window);
            }
            break;
            case GLFW_KEY_SPACE: { 
                std::cout << &recWords << std::endl;

                // Draw a square at a specific position on the screen
                int xStart = 100;
                int yStart = 100;
                int xEnd = 200;
                int yEnd = 200;
                // Show the dialog window
    

                // Make the OpenGL context of the window current
                glfwMakeContextCurrent(window);

                // Draw your scene here
                drawBoundingBox(xStart, yStart, xEnd, yEnd);
            shouldExit = true;

                // Swap front and back buffers
                glfwSwapBuffers(window);
                    }
            break;
            case GLFW_KEY_D: {

                // Make the OpenGL context of the window current
                glfwMakeContextCurrent(window);

                // Draw your scene here
                // drawBoundingBox(xStart, yStart, xEnd, yEnd);
                renderFlag= true;
                translationText = "Hello пейсымалар!";
                                // Swap front and back buffers
                glfwSwapBuffers(window);
            }
            break;
        }
        
    }
}


// Callback function for the dialog response



int run_detection(){ 
    //    gtk_init(NULL, NULL);
    DetectedWords recWords = analyzeScreen();
    RecognizedWordData recWordsData;
    recWordsData.recWords = &recWords; 
            shouldExit = false;

    // Initialize GLFW
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    // Retrieve the primary monitor
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();



    // Create a GLFW window
    // GLFWwindow* window = glfwCreateWindow(2560, 1440, "Keyboard Events", NULL, NULL);
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

    GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "Fullscreen Window", primaryMonitor, NULL);
    glfwSetWindowUserPointer(window, &recWordsData);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    std::cout << window << "Main loop" << std::endl;
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
     glfwSetKeyCallback(window, keyCallback);

    // Make the OpenGL context of the window current
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImFont* font = io.Fonts->AddFontFromFileTTF("/home/jasos/.local/share/lutris/runners/wine/lutris-GE-Proton8-5-x86_64/share/wine/fonts/arial.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
if (font == NULL) {
    // Handle error
    std::cout << "Failed to load font" << std::endl;
    return -1;
}
     ImGui::StyleColorsDark();
    // Setup Platform/Renderer bindings

 ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Set the keyboard callback function
   
    glfwSetWindowCloseCallback(window, windowCloseCallback);

    // Loop until the user closes the window
    // Loop until the user closes the window
while (!glfwWindowShouldClose(window) && !shouldExit)
{
    // Make the OpenGL context of the window current
    glfwMakeContextCurrent(window);
    for(int i = 0; i < recWords.selectedWords.size(); i++){
        drawBoundingBox(recWords.selectedWords[i].position.x1, recWords.selectedWords[i].position.y1, recWords.selectedWords[i].position.x2, recWords.selectedWords[i].position.y2);
    }

        renderImGuiWindow(font);
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

//  // // // // // // // // // // //template <typename T>



int main() {
        std::cout << "halloloooo" <<std::endl;
    // Open the display connection
    Display* display = XOpenDisplay(nullptr);

    // Variables for XInput extension
    int xi_opcode, event, error;

    // Check if XInput extension is available
    if (!XQueryExtension(display, "XInputExtension", &xi_opcode, &event, &error)) {
        // XInput extension not available
        // Handle the error or exit the program
        std::cout << "No" << std::endl;  
    }

    // Get the root window of the display
    Window rootWindow = DefaultRootWindow(display);

    // Set up event mask to select keyboard events
    XIEventMask evmask{};
    unsigned char mask[(XI_LASTEVENT + 7)/8] = { 0 };
    evmask.deviceid = XIAllDevices;
    evmask.mask_len = sizeof(mask);
    evmask.mask = mask;
    XISetMask(mask, XI_KeyPress);
    XISetMask(mask, XI_KeyRelease);

    // Select the events to capture using XInput2
    XISelectEvents(display, rootWindow, &evmask, 1);

    // Event capture loop
while (true) {
    // Get the next event from the event queue
    XEvent xevent;
    XNextEvent(display, &xevent);

    // Check if it's an XInput event
    if (xevent.xcookie.type == GenericEvent && xevent.xcookie.extension == xi_opcode) {
        // Retrieve the XInput event data
        XGetEventData(display, &xevent.xcookie);
        XGenericEventCookie* cookie = &xevent.xcookie;

        // Check if it's a keyboard event
        if (cookie->evtype == XI_KeyPress || cookie->evtype == XI_KeyRelease) {
            // Retrieve the keyboard event data
            XIDeviceEvent* xievent = reinterpret_cast<XIDeviceEvent*>(cookie->data);
            int keycode = xievent->detail;
            std::cout << "Keycode: " << keycode << std::endl;
            std::cout << "Keycode (hex): " << std::hex << static_cast<unsigned int>(keycode) << std::endl;

            // Check for the specific key combination
            KeyCode ctrlKeyCode = XKeysymToKeycode(display, XK_Control_L);
            KeyCode dotKeyCode = XKeysymToKeycode(display, XK_period);

            if (keycode == ctrlKeyCode &&  (xievent->mods.effective & ControlMask)) {
                // Key combination Ctrl+. is pressed
                // Handle the specific key combination here
                std::cout << "Ctrl+. is pressed" << std::endl;
                run_detection();
            }
            // Free the event data
            XFreeEventData(display, &xevent.xcookie);
        }
    }
}


    // Close the display connection
    XCloseDisplay(display);
    return 0;
}
// #include <opencv2/opencv.hpp>
// #include <tesseract/baseapi.h>
// #include <leptonica/allheaders.h>
// #include <leptonica/alltypes.h> // This line includes the necessary definitions
// #include <X11/Xlib.h>
// #include <X11/Xutil.h>

// cv::Mat preprocess_image(cv::Mat& img)
// {
//     cv::Mat gray, blurred, binary;
    
//     // Convert the image to grayscale
//     cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    
//     // Reduce noise with Gaussian blur
//     // cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);
    
//     // Binarize image using Otsu's method
//     cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    
//     return binary;
// }

// void detect_words(cv::Mat& img)
// {
//     // Initialize tesseract-ocr API
//     tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();

//     // Set the tessdata path and language to use
//     if (ocr->Init(NULL, "eng")) {
//         std::cerr << "Could not initialize tesseract.\n";
//         exit(1);
//     }

//     // Set image data
//     ocr->SetImage(img.data, img.cols, img.rows, 3, img.step);

//     // Get the text results
//     tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
//     tesseract::PageIterator* it = ocr->AnalyseLayout();
//     if (it != 0) {
//         do {
//             int left, top, right, bottom;
//             it->BoundingBox(level, &left, &top, &right, &bottom);
//             cv::rectangle(img, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(255, 255, 255), 2);
//         } while (it->Next(level));
//     }

//     // Show the image with OpenCV
//     cv::imshow("Image", img);
//     cv::waitKey(0);

//     // Destroy used object and release memory
//     ocr->End();
//     delete ocr;
//     delete it;
// }


// int main() {
//     Display* display = XOpenDisplay(nullptr);
//     Window root = DefaultRootWindow(display);

//     XWindowAttributes gwa;

//     XGetWindowAttributes(display, root, &gwa);
//     int width = gwa.width;
//     int height = gwa.height;

//     XImage* image = XGetImage(display,root, 0,0 , width,height,AllPlanes, ZPixmap);

//     unsigned char *array = new unsigned char[width * height * 3];
//     cv::Mat m(height, width, CV_8UC3, array);
//     // cv::imshow("Image", m);
//     for (int y = 0; y < height; ++y) {
//         for (int x = 0; x < width; ++x) {
//             unsigned long pixel = XGetPixel(image,x,y);
//             unsigned char blue = pixel & 0xff;
//             unsigned char green = (pixel & 0xff00) >> 8;
//             unsigned char red = (pixel & 0xff0000) >> 16;

//             array[(x + y * width) * 3 + 0] = blue;
//             array[(x + y * width) * 3 + 1] = green;
//             array[(x + y * width) * 3 + 2] = red;
//         }
//     }
//     // cv::imshow("Image", m);
//     cv::Mat n = preprocess_image(m);
//     // Now you can pass cv::Mat m to your detect_words function
//     detect_words(n);

//     XFree(image);
//     XCloseDisplay(display);

//     return 0;
// }
