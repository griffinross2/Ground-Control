#pragma once

#include "app_window.h"

#include "imgui.h"

#include <array>

constexpr ImGuiKey DEBUG_OVERLAY_TOGGLE = ImGuiKey_F3;
constexpr int DEBUG_FRAME_TIME_HISTORY_SIZE = 200;
constexpr float DEBUG_GRAPH_MAX_TIME = 0.1f;  // seconds
constexpr float DEBUG_GRAPH_WIDTH = 200.0f;   // pixels
constexpr float DEBUG_GRAPH_HEIGHT = 75.0f;   // pixels

class DebugOverlay : public AppWindow {
public:
    DebugOverlay();
    ~DebugOverlay();
    void Update() override;
    void Render() override;

private:
    std::array<float, DEBUG_FRAME_TIME_HISTORY_SIZE> m_frameTimes;
    int m_frameTimeSize = 0;
};
