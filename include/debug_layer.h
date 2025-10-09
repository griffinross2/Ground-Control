#pragma once

#include "app_layer.h"

class DebugLayer : public AppLayer {
public:
    DebugLayer();
    ~DebugLayer();
    void Update() override;
    void Render() override;

private:
};