#include "main_window.h"

#include "application.h"

#include "GLFW/glfw3.h"
#include "imgui.h"

MainWindow::MainWindow() {

}

MainWindow::~MainWindow() {

}

void MainWindow::Render() {
    int w, h;
    glfwGetWindowSize(g_appInstance->GetWindow(), &w, &h);
    ImGui::SetNextWindowSize(ImVec2(w, h));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Main", nullptr,
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
        
    ImGui::Text("Welcome to Ground Control!");
 
    ImGui::End();

    m_btWindow.Render();
}

void MainWindow::Update() {
    m_btWindow.Update();
}