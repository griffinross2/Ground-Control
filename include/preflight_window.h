#pragma once

#include "app_window.h"

class PreflightWindow : public AppWindow {
public:
    PreflightWindow();
    ~PreflightWindow();

    void Update() override;
    void Render() override;

private:
};
