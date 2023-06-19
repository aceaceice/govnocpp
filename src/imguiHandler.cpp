#include <GLFW/glfw3.h>
#include "imguiHandler.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "detection.h"
#include "utils.h"
#include <iostream>
#include <string>
void renderImGuiWindow(ImFont* font, DetectedWords* recWordsPtr)
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::PushFont(font);
    // ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 100), ImVec2(-1, FLT_MAX));
    ImGui::Begin("Translate");
    std::string text = recWordsPtr->translationText;
    std::string error = recWordsPtr->detectionError;
    //     static char textBuffer[256] = ""; // Buffer to store the input text

    std::string str = recWordsPtr->selectedText;
char buffer[512];

str.copy(buffer, str.size() + 1);
buffer[str.size()] = '\0'; // Ensure null-terminated
ImGui::PushItemWidth(-1);
if (ImGui::InputText("##", buffer, sizeof(buffer)))
{
    // This block is executed when the text is changed
    // 'buffer' contains the text

    // Update 'str'
    str = buffer;
    recWordsPtr->updateSelectedText(str);
}
    // std::cout << text << std::endl;
    // std::cout << recWordsPtr << std::endl;
    // std::cout << *text << std::endl;
    ImGui::TextWrapped("%s", text.c_str());
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", error.c_str());

    ImGui::Dummy(ImVec2(0, ImGui::GetContentRegionAvail().y - ImGui::GetFrameHeightWithSpacing()));


    float windowCenter = ImGui::GetWindowWidth() / 2.0f;
    float buttonsWidthHalf = (3 * ImGui::CalcTextSize("Save").x + 2 * ImGui::GetStyle().ItemSpacing.x) / 2.0f;
    ImGui::SetCursorPosX(windowCenter - buttonsWidthHalf);

if (ImGui::Button("Save"))                         
{
    writeToFile(recWordsPtr->translationText, recWordsPtr);
}

ImGui::SameLine();

if (ImGui::Button("Clear"))                         
{
    recWordsPtr->clearSelected();
}

ImGui::SameLine();

if (ImGui::Button("Exit"))                         
{
    recWordsPtr->shouldExit = true;
}


    ImGui::End();
    ImGui::PopFont();
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Clear with alpha set to 0
    // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}