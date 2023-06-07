// #include <tesseract/baseapi.h>
// #include <fstream>
// #include <iostream>
// #include <leptonica/allheaders.h>
// #include <GLFW/glfw3.h>
// #include "screenCapture.h"
// #include "detection.h"
// #include "analyzeScreen.h"

// #include <gtk/gtk.h>
// #include <ft2build.h>
// #include FT_FREETYPE_H

// #include <X11/Xlib.h>
// #include <X11/X.h>
// #include <X11/Xutil.h>
// #include <X11/keysym.h>
// #include <X11/extensions/XInput2.h>
// // #include <X11/extensions/XInput.h> // Include XInput extension header
// #include <typeinfo>



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

// void renderText(GLFWwindow* window, const char* text, float x, float y, float scale)
// {
//     int width, height;
//     glfwGetWindowSize(window, &width, &height);

//     glMatrixMode(GL_PROJECTION);
//     glPushMatrix();
//     glLoadIdentity();
//     glOrtho(0, width, 0, height, -1, 1);
//     glMatrixMode(GL_MODELVIEW);
//     glPushMatrix();
//     glLoadIdentity();

//     glTranslatef(x, y, 0);
//     glScalef(scale, scale, 1.0f);

//     glColor3f(0.0f, 0.0f, 0.0f);
//     glfwSetWindowTitle(window, text);

//     glPopMatrix();
//     glMatrixMode(GL_PROJECTION);
//     glPopMatrix();
//     glMatrixMode(GL_MODELVIEW);
// }

// void dupa(){
//     std::cout << "sdasdsadasd" << std::endl;
// }

// struct DialogData {
//     const char* text;
//     GLFWwindow* window;
// };
// bool shouldExit = false;
// void windowCloseCallback(GLFWwindow* window){
//     std::cout << "asdasdasdasdas 12312 " << std::endl;
//     std::cout << window << "Shit loop" << std::endl;
//             glfwSetWindowShouldClose(window, GLFW_TRUE);


// }

// void writeToFile(const std::string& text, GLFWwindow* window) {
//     std::ofstream file("saved.txt", std::ios::app); // Open the file in append mode

//     if (file.is_open()) {
//         file << text << std::endl; // Write the text to the file
//         file.close();              // Close the file
//         std::cout << "Text written to file successfully." << std::endl;
//         // windowCloseCallback(window);

//         glfwTerminate();
//     } else {
//         std::cout << "Error opening file." << std::endl;
//     }
// }

// void exitLoop(){
//             shouldExit = true;

// }

// static void dialog_response_callback(GtkDialog *dialog, gint response_id, gpointer user_data)
// {   

//     DialogData* userData = static_cast<DialogData*>(user_data);
//     // Handle the response here
//     switch (response_id)
//     {
//         case GTK_RESPONSE_OK:
//             // Handle OK response
//             dupa();
//             writeToFile(userData->text, userData->window);
//         windowCloseCallback(userData->window);
//             shouldExit = true;
//             g_print("OK button clicked\n");
//             break;

//         case GTK_RESPONSE_CANCEL:
//             // Handle Cancel response
//             exitLoop();
//             shouldExit = true;
//             g_print("Cancel button clicked\n");    
//             break;

//         case GTK_RESPONSE_CLOSE:
//             // Handle Close response
//             g_print("Close button clicked\n");
//             break;

//         default:
//             // Handle other responses
//             g_print("Response ID: %d\n", response_id);
//             break;
//     }

//     // Convert the response_id to a string
//     gchar *response_str = g_strdup_printf("Response ID: %d", response_id);

//     // Create a message dialog to display the response
//     // GtkWidget *message_dialog = gtk_message_dialog_new(
//     //     GTK_WINDOW(dialog),                    // Parent window
//     //     GTK_DIALOG_DESTROY_WITH_PARENT,        // Destroy with parent
//     //     GTK_MESSAGE_INFO,                      // Message type (info)
//     //     GTK_BUTTONS_OK,                        // Buttons (OK)
//     //     response_str                           // Response string
//     // );

//     // Set the dialog title
//     // gtk_window_set_title(GTK_WINDOW(message_dialog), "Response");
//     // GtkWidget *label = gtk_label_new("Hello, World!");
//     // gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(message_dialog))), label);

//     // // Show the dialog
//     // gtk_widget_show_all(message_dialog);

//     // // Run the dialog and destroy it when closed
//     // gtk_dialog_run(GTK_DIALOG(message_dialog));
//     // gtk_widget_destroy(message_dialog);

//     // Free the allocated string
//     g_free(response_str);
// }

// void show_dialog(const char* dialogText, GLFWwindow* window)
// {
//     GtkWidget *dialog;
//     int flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
//     GtkWindow *parent_window = NULL; // Set the parent window if desired

//     // Create the dialog window
//     dialog = gtk_dialog_new_with_buttons(
//         "Dialog Window",                    // Dialog title
//         parent_window,                       // Parent window
//         static_cast<GtkDialogFlags>(flags),  // Dialog flags
//         "_OK", GTK_RESPONSE_OK,              // OK button
//         "_Cancel", GTK_RESPONSE_CANCEL,      // Cancel button
//         NULL                                 // End of button list
//     );

//     DialogData* userData = new DialogData;
//     userData->text = dialogText;
//     userData->window = window;

//         GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
//      // Create a label widget
//     GtkWidget *label = gtk_label_new(dialogText);

//     // Add the label widget to the main window
//     gtk_container_add(GTK_CONTAINER(content_area), label);

//     // Connect the response signal to the callback function
//     g_signal_connect(dialog, "response", G_CALLBACK(dialog_response_callback), userData);

//     // Show the dialog window
//     gtk_widget_show_all(dialog);
// }

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
//                 RecognizedWord initialWord = recWords.findMatchingWord(event.xbutton.x, event.xbutton.y);
//                 // recWords.selectWord(initialWordId);
//                 // Coordinates initialWord = recWords.getBoundingBox(initialWordId);
//                 // std::cout << initialWord.position.x1 << "  " << initialWord.position.x2 << std::endl;
//                 drawBoundingBox(initialWord.position.x1, initialWord.position.y1, initialWord.position.x2, initialWord.position.y2);
//                 glfwSwapBuffers(window);

//             }
//             break;
//             case GLFW_KEY_Q: {
//                 glfwMakeContextCurrent(window);
//                 std::cout<<"TES" << std::endl;
            
//                 RecognizedWord prevWord = recWords.selectPrev();
//                 std::cout << prevWord.position.x1 << "  " << prevWord.position.x2 << "y dim" << prevWord.position.y1 << "  " << prevWord.position.y2<< std::endl;
//                 drawBoundingBox(prevWord.position.x1, prevWord.position.y1, prevWord.position.x2, prevWord.position.y2);
//                 glfwSwapBuffers(window);
            
//             }
//             break;
//             case GLFW_KEY_E: {
//                 glfwMakeContextCurrent(window);
//                 std::cout<<"TES" << std::endl;
            
//                 RecognizedWord nextWord = recWords.selectNext();
//                 // std::cout << prevWord.position.x1 << "  " << prevWord.position.x2 << "y dim" << prevWord.position.y1 << "  " << prevWord.position.y2<< std::endl;
//                 drawBoundingBox(nextWord.position.x1, nextWord.position.y1, nextWord.position.x2, nextWord.position.y2);
//                 glfwSwapBuffers(window);
            
//             }
//             break;
//             case GLFW_KEY_T: {
//                  glfwMakeContextCurrent(window);

//                 // Draw your scene here
//                 std::string translation = recWords.translateSelected();
//                 const char* cTranslation = translation.c_str();
//                 show_dialog(cTranslation, window);

//     // Start the main GTK+ loop

//                 // Swap front and back buffers
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
//                 // Show the dialog window
    

//                 // Make the OpenGL context of the window current
//                 glfwMakeContextCurrent(window);

//                 // Draw your scene here
//                 drawBoundingBox(xStart, yStart, xEnd, yEnd);
//             shouldExit = true;

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


// // Callback function for the dialog response



// int main()
// {    gtk_init(NULL, NULL);
//     DetectedWords recWords = analyzeScreen();
//     RecognizedWordData recWordsData;
//     recWordsData.recWords = &recWords; 
//             shouldExit = false;

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
//     std::cout << window << "Main loop" << std::endl;
//     if (!window)
//     {
//         glfwTerminate();
//         return -1;
//     }
//     // Set the keyboard callback function
//     glfwSetKeyCallback(window, keyCallback);

//     // Make the OpenGL context of the window current
//     glfwMakeContextCurrent(window);

//     glfwSetWindowCloseCallback(window, windowCloseCallback);

//     // Loop until the user closes the window
//     // Loop until the user closes the window
// while (!glfwWindowShouldClose(window) && !shouldExit)
// {
//     // Poll for and process events
//     glfwPollEvents();

//     // Check if the window should be closed
//     if (shouldExit){

//         break;
//     }

//     // Your other rendering and logic code here
// }

// // Terminate GLFW
// glfwTerminate();
//     return 0;
// }

// //  // // // // // // // // // // //template <typename T>



// // int main() {
// //         std::cout << "halloloooo" <<std::endl;
// //     // Open the display connection
// //     Display* display = XOpenDisplay(nullptr);

// //     // Variables for XInput extension
// //     int xi_opcode, event, error;

// //     // Check if XInput extension is available
// //     if (!XQueryExtension(display, "XInputExtension", &xi_opcode, &event, &error)) {
// //         // XInput extension not available
// //         // Handle the error or exit the program
// //         std::cout << "No" << std::endl;  
// //     }

// //     // Get the root window of the display
// //     Window rootWindow = DefaultRootWindow(display);

// //     // Set up event mask to select keyboard events
// //     XIEventMask evmask{};
// //     unsigned char mask[(XI_LASTEVENT + 7)/8] = { 0 };
// //     evmask.deviceid = XIAllDevices;
// //     evmask.mask_len = sizeof(mask);
// //     evmask.mask = mask;
// //     XISetMask(mask, XI_KeyPress);
// //     XISetMask(mask, XI_KeyRelease);

// //     // Select the events to capture using XInput2
// //     XISelectEvents(display, rootWindow, &evmask, 1);

// //     // Event capture loop
// // while (true) {
// //     // Get the next event from the event queue
// //     XEvent xevent;
// //     XNextEvent(display, &xevent);

// //     // Check if it's an XInput event
// //     if (xevent.xcookie.type == GenericEvent && xevent.xcookie.extension == xi_opcode) {
// //         // Retrieve the XInput event data
// //         XGetEventData(display, &xevent.xcookie);
// //         XGenericEventCookie* cookie = &xevent.xcookie;

// //         // Check if it's a keyboard event
// //         if (cookie->evtype == XI_KeyPress || cookie->evtype == XI_KeyRelease) {
// //             // Retrieve the keyboard event data
// //             XIDeviceEvent* xievent = reinterpret_cast<XIDeviceEvent*>(cookie->data);
// //             int keycode = xievent->detail;
// //             std::cout << "Keycode: " << keycode << std::endl;
// //             std::cout << "Keycode (hex): " << std::hex << static_cast<unsigned int>(keycode) << std::endl;

// //             // Check for the specific key combination
// //             KeyCode ctrlKeyCode = XKeysymToKeycode(display, XK_Control_L);
// //             KeyCode dotKeyCode = XKeysymToKeycode(display, XK_period);

// //             if (keycode == ctrlKeyCode && (xievent->mods.effective & ControlMask)) {
// //                 // Key combination Ctrl+. is pressed
// //                 // Handle the specific key combination here
// //                 std::cout << "Ctrl+. is pressed" << std::endl;
// //                 run_detection();
// //             }
// //             // Free the event data
// //             XFreeEventData(display, &xevent.xcookie);
// //         }
// //     }
// // }


// //     // Close the display connection
// //     XCloseDisplay(display);
// //     return 0;
// // }



#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main() {
    // Initialize the library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create an ImGui window and render some text
        ImGui::Begin("ImGui Window");                          // Create a window called "ImGui Window" and append into it.
        ImGui::Text("This is some useful text.");              // Display some text

        // Add two buttons
        if (ImGui::Button("Button 1"))                         // if Button is pressed
        {
            std::cout << "Button 1 is pressed." << std::endl;
        }

        if (ImGui::Button("Button 2"))                         // if Button is pressed
        {
            std::cout << "Button 2 is pressed." << std::endl;
        }

        ImGui::End();

        // Render ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
