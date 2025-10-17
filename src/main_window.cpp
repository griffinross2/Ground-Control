#include "main_window.h"

#include "application.h"

#include "GLFW/glfw3.h"
#include "imgui.h"

MainWindow::MainWindow() {}

MainWindow::~MainWindow() {}

void MainWindow::Render() {
    int w, h;
    glfwGetWindowSize(g_appInstance->GetWindow(), &w, &h);
    ImGui::SetNextWindowSize(ImVec2(w, h));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Main", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav |
                     ImGuiWindowFlags_NoBringToFrontOnFocus |
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    // BEGIN MAIN WINDOW CONTENT

    // Flight info tabs
    switch (m_flightStageTab) {
        case 0:
            m_preflightWindow.Render();
            break;
        case 1:
            m_flightWindow.Render();
            break;
        case 2:
            m_postflightWindow.Render();
            break;
    }

    // Flight stage selection buttons
    float buttonWidth =
        w / 3.0f - ImGui::GetStyle().ItemSpacing.x * 4.0f / 3.0f;
    float buttonY = ImGui::GetWindowContentRegionMax().y -
                    ImGui::GetFrameHeightWithSpacing() - 10.0f;
    int nextFlightStageTab = m_flightStageTab;  // To defer update

    ImGui::SetCursorPosY(buttonY);

    if (m_flightStageTab == 0)
        ImGui::BeginDisabled();
    if (ImGui::Button("Preflight", ImVec2(buttonWidth, 40.0f)))
        nextFlightStageTab = 0;
    if (m_flightStageTab == 0)
        ImGui::EndDisabled();

    ImGui::SameLine();

    if (m_flightStageTab == 1)
        ImGui::BeginDisabled();
    if (ImGui::Button("Flight", ImVec2(buttonWidth, 40.0f)))
        nextFlightStageTab = 1;
    if (m_flightStageTab == 1)
        ImGui::EndDisabled();

    ImGui::SameLine();

    if (m_flightStageTab == 2)
        ImGui::BeginDisabled();
    if (ImGui::Button("Postflight", ImVec2(buttonWidth, 40.0f)))
        nextFlightStageTab = 2;
    if (m_flightStageTab == 2)
        ImGui::EndDisabled();

    m_flightStageTab = nextFlightStageTab;

    // END MAIN WINDOW CONTENT

    ImGui::End();

    m_btWindow.Render();
}

void MainWindow::Update() {
    m_btWindow.Update();
    m_preflightWindow.Update();
    m_flightWindow.Update();
    m_postflightWindow.Update();
}