#pragma once

#include "app_window.h"

class FlightWindow : public AppWindow {
public:
    FlightWindow();
    ~FlightWindow();

    void Update() override;
    void Render() override;

private:
};
