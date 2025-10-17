#pragma once

#include "app_window.h"

class PostflightWindow : public AppWindow {
public:
    PostflightWindow();
    ~PostflightWindow();

    void Update() override;
    void Render() override;

private:
};
