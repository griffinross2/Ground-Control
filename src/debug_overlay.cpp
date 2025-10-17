#include "debug_overlay.h"

#include "application.h"

#include <algorithm>
#include <format>

DebugOverlay::DebugOverlay() {}

DebugOverlay::~DebugOverlay() {}

void DebugOverlay::Update() {
	if (ImGui::IsKeyPressed(DEBUG_OVERLAY_TOGGLE, false))
		m_visible = !m_visible;

    if (m_frameTimeSize < DEBUG_FRAME_TIME_HISTORY_SIZE) {
        m_frameTimes[m_frameTimeSize] = ImGui::GetIO().DeltaTime;
        m_frameTimeSize++;
    } else {
        std::rotate(m_frameTimes.begin(), m_frameTimes.begin() + 1,
                    m_frameTimes.end());
        m_frameTimes[DEBUG_FRAME_TIME_HISTORY_SIZE - 1] =
            ImGui::GetIO().DeltaTime;
    }
}

void DebugOverlay::Render() {
	if (!m_visible)
		return;
    // Background
    ImGui::GetForegroundDrawList()->AddRectFilled(
        ImVec2(5.0f, 5.0f),
        ImVec2(DEBUG_GRAPH_WIDTH * g_appInstance->m_uiScale + 5.0f,
               DEBUG_GRAPH_HEIGHT * g_appInstance->m_uiScale + 5.0f),
        IM_COL32(40, 40, 40, 180));

    // Graph lines
    for (int i = 0; i < m_frameTimeSize - 1; i++) {
        ImVec2 start =
            ImVec2(5.0f + (i * (DEBUG_GRAPH_WIDTH * g_appInstance->m_uiScale) /
                           DEBUG_FRAME_TIME_HISTORY_SIZE),
                   5.0f + (DEBUG_GRAPH_HEIGHT * g_appInstance->m_uiScale) -
                       (m_frameTimes[i] *
                        (DEBUG_GRAPH_HEIGHT * g_appInstance->m_uiScale) /
                        DEBUG_GRAPH_MAX_TIME));

        ImVec2 end = ImVec2(
            5.0f + ((i + 1) * (DEBUG_GRAPH_WIDTH * g_appInstance->m_uiScale) /
                    DEBUG_FRAME_TIME_HISTORY_SIZE),
            5.0f + (DEBUG_GRAPH_HEIGHT * g_appInstance->m_uiScale) -
                (m_frameTimes[i + 1] *
                 (DEBUG_GRAPH_HEIGHT * g_appInstance->m_uiScale) /
                 DEBUG_GRAPH_MAX_TIME));

        ImGui::GetForegroundDrawList()->AddLine(start, end,
                                                IM_COL32(255, 255, 255, 255));
    }

    // FPS Text
    ImGui::GetForegroundDrawList()->AddText(
        ImGui::GetFont(), 16 * g_appInstance->m_uiScale, ImVec2(10.0f, 10.0f),
        IM_COL32(255, 255, 255, 255),
        std::format("FPS: {:.2f}", ImGui::GetIO().Framerate).c_str());
}
