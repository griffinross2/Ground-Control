#include "debug_layer.h"

#include "application.h"

#include <format>

#include "imgui.h"

DebugLayer::DebugLayer() {}

DebugLayer::~DebugLayer() {}

void DebugLayer::Update() {}

void DebugLayer::Render() {
    // Draw FPS in the top-left corner
    ImGui::GetBackgroundDrawList()->AddText(
        ImGui::GetFont(), 16 * g_appInstance->m_uiScale, ImVec2(10.0f, 10.0f),
        IM_COL32(255, 255, 255, 255),
        std::format("FPS: {:.2f}", ImGui::GetIO().Framerate).c_str());
}