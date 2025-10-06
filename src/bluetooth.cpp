#include "bluetooth.h"

BluetoothManager::BluetoothManager() : scanning(false) {
    if (SimpleBLE::Adapter::bluetooth_enabled()) {
        adapter = SimpleBLE::Adapter::get_adapters()[0];
        adapter.set_callback_on_scan_updated(
            [this](SimpleBLE::Peripheral p) { this->scanCallback(p); });
    }
}

BluetoothManager::~BluetoothManager() {
    if (scanning) {
        adapter.scan_stop();
    }
}

void BluetoothManager::startScan() {
    if (!scanning && SimpleBLE::Adapter::bluetooth_enabled()) {
        // It might not be initialized if bluetooth was off when the class was
        // initialized
        if (!adapter.initialized()) {
            adapter = SimpleBLE::Adapter::get_adapters()[0];
            adapter.set_callback_on_scan_updated(
                [this](SimpleBLE::Peripheral p) { this->scanCallback(p); });
        }

        adapter.scan_start();
        scanning = true;
    }
}

void BluetoothManager::stopScan() {
    if (scanning) {
        adapter.scan_stop();
        scanning = false;
    }
}

void BluetoothManager::connect(const std::string& address) {
    for (auto& device : devices) {
        if (device.peripheral.address() == address) {
            device.peripheral.connect();
            return;
        }
    }
}

bool BluetoothManager::isScanning() const {
    return scanning;
}

bool BluetoothManager::isBluetoothEnabled() const {
    return SimpleBLE::Adapter::bluetooth_enabled();
}

std::vector<BLEPeripheralInfo> BluetoothManager::getDevices() const {
    return devices;
}

void BluetoothManager::scanCallback(SimpleBLE::Peripheral p) {
    BLEPeripheralInfo info;
    info.peripheral = p;
    info.rssi = p.rssi();

    // Don't re-add a device, update the info
    for (auto& device : devices) {
        if (device.peripheral.address() == p.address()) {
            device.rssi = p.rssi();
            return;
        }
    }
    devices.push_back(info);
}