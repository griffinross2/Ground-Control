#pragma once

#include "app_window.h"
#include "bluetooth_window.h"

class MainWindow : public AppWindow {
public:
    MainWindow();
    ~MainWindow();
    void Update() override;
    void Render() override;

private:
    BluetoothWindow m_btWindow;
};