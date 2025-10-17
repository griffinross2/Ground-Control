#pragma once

#include "app_window.h"
#include "bluetooth.h"

class BluetoothWindow : public AppWindow {
public:
    BluetoothWindow();
    ~BluetoothWindow();
    void Update() override;
    void Render() override;

private:
    bool m_btEnabled = true;
    int m_selectedRow = -1;
    BluetoothManager m_ble;
    BLEPeripheralInfo m_pConnected;
};