#pragma once

#include <simpleble/SimpleBLE.h>

#include <vector>

class PeripheralInfo {
public:
    std::string name;
    std::string address;
    int rssi;
};

class BluetoothManager {
public:
    BluetoothManager();
    ~BluetoothManager();

    void startScan();
    void stopScan();
    bool isScanning() const;
    bool isBluetoothEnabled() const;
    std::vector<PeripheralInfo> getDevices() const;

private:
    void scanCallback(SimpleBLE::Peripheral p);

    bool scanning;
    SimpleBLE::Adapter adapter;
    std::vector<PeripheralInfo> devices;
};