#pragma once

#include <simpleble/SimpleBLE.h>

#include <vector>

class BLEPeripheralInfo {
public:
    SimpleBLE::Peripheral peripheral;
    int rssi = -100;
};

class BluetoothManager {
public:
    BluetoothManager();
    ~BluetoothManager();

    void startScan();
    void stopScan();
    void connect(const std::string& address);
    bool isScanning() const;
    bool isBluetoothEnabled() const;
    std::vector<BLEPeripheralInfo> getDevices() const;

private:
    void scanCallback(SimpleBLE::Peripheral p);

    bool scanning;
    SimpleBLE::Adapter adapter;
    std::vector<BLEPeripheralInfo> devices;
};