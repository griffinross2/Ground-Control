#pragma once

#include "app_layer.h"

#include <array>

#define DEBUG_FRAME_TIME_HISTORY_SIZE 200
#define DEBUG_GRAPH_MAX_TIME 0.1f  // seconds
#define DEBUG_GRAPH_WIDTH 200.0f   // pixels
#define DEBUG_GRAPH_HEIGHT 75.0f   // pixels

class DebugLayer : public AppLayer {
public:
    DebugLayer();
    ~DebugLayer();
    void Update() override;
    void Render() override;

private:
    std::array<float, DEBUG_FRAME_TIME_HISTORY_SIZE> m_frameTimes;
    int m_frameTimeSize = 0;
};