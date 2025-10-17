#pragma once

#include "app_window.h"
#include "bluetooth_window.h"
#include "flight_window.h"
#include "postflight_window.h"
#include "preflight_window.h"

class MainWindow : public AppWindow {
public:
    MainWindow();
    ~MainWindow();
    void Update() override;
    void Render() override;

private:
    int m_flightStageTab = 0;

    BluetoothWindow m_btWindow;
    PreflightWindow m_preflightWindow;
    FlightWindow m_flightWindow;
    PostflightWindow m_postflightWindow;
};