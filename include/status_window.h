#pragma once

#include "app_window.h"

class StatusWindow : public AppWindow {
public:
    StatusWindow();
    ~StatusWindow();

    void Update() override;
    void Render() override;

private:
    int m_selectedTab = -1;
};
