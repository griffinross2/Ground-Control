#pragma once

#include "app_layer.h"
#include "bluetooth.h"

class BluetoothLayer : public AppLayer {
public:
    BluetoothLayer();
    ~BluetoothLayer();
    void Update() override;
    void Render() override;

private:
    bool m_btEnabled = true;
    int m_selectedRow = -1;
    BluetoothManager m_ble;
    BLEPeripheralInfo m_pConnected;
};