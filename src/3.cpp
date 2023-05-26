// #define GL_SILENCE_DEPRECATION
// #include <GLFW/glfw3.h>

// int main() {
//     glfwInit();

//     glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
//     GLFWwindow* window = glfwCreateWindow(800, 600, "Transparent Window", NULL, NULL);

//     glfwMakeContextCurrent(window);
//     glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     glfwShowWindow(window);

//     while (!glfwWindowShouldClose(window)) {
//         glClear(GL_COLOR_BUFFER_BIT);
//         // render here
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwTerminate();
//     return 0;
// }
