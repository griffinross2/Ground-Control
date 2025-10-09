#include "bluetooth_layer.h"

#include "application.h"

#include "imgui.h"

constexpr const int TEXT_WIDTH_PADDING = 10;  // pixels
constexpr const float TABLE_MAX_HEIGHT = 350.0f;

void centerItem(float itemWidth) {
    float window_width = ImGui::GetWindowSize().x;

    ImGui::SetCursorPosX((window_width - itemWidth) / 2.0f);
}

BluetoothLayer::BluetoothLayer() {}

BluetoothLayer::~BluetoothLayer() {}

void BluetoothLayer::Update() {}

void BluetoothLayer::Render() {
    if (!m_ble.isBluetoothEnabled() && m_btEnabled) {
        const char* text =
            "Warning: Bluetooth is not enabled on your device.\nMost "
            "functions will not work if Bluetooth is not enabled.";

        ImVec2 text_size = ImGui::CalcTextSize(text);
        ImGui::SetNextWindowSize(ImVec2(0, 0));
        ImGui::Begin("Warning", &m_btEnabled, ImGuiWindowFlags_NoResize);

        ImGui::Text(text);

        centerItem(ImGui::CalcTextSize("OK").x + TEXT_WIDTH_PADDING);
        if (ImGui::Button("OK")) {
            m_btEnabled = false;
        }

        ImGui::End();
    }

    ImGui::Begin("Bluetooth Devices");
    ImGui::Text("Select a device to pair with.");

    ImVec2 space = ImGui::GetContentRegionAvail();
    if (ImGui::BeginTable(
            "main", 3,
            ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Borders |
                ImGuiTableFlags_ScrollY,
            ImVec2(0.0f, space.y - ImGui::GetFrameHeight() -
                             2 * ImGui::GetStyle().FramePadding.y))) {
        ImGui::TableSetupColumn("Device Name",
                                ImGuiTableColumnFlags_WidthStretch, 2.0f);
        ImGui::TableSetupColumn("Bluetooth Address",
                                ImGuiTableColumnFlags_WidthStretch, 2.0f);
        ImGui::TableSetupColumn("RSSI", ImGuiTableColumnFlags_WidthStretch,
                                1.0f);

        ImGui::TableHeadersRow();

        for (size_t i = 0; auto& p : m_ble.getDevices()) {
            if (p.peripheral.identifier().length() > 0) {
                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                ImGui::Text(p.peripheral.identifier().c_str());

                ImGui::TableSetColumnIndex(1);
                ImGui::Text(p.peripheral.address().c_str());

                ImGui::TableSetColumnIndex(2);
                ImGui::BeginDisabled();
                ImGui::SetNextItemWidth(-1);
                ImGui::SliderInt(std::format("##ble_table_rssi{:d}", i).c_str(),
                                 &p.rssi, -100, 0,
                                 std::format("{:2d} dBm", p.rssi).c_str(),
                                 ImGuiSliderFlags_NoInput);
                ImGui::EndDisabled();

                ImGui::SameLine();
                if (ImGui::Selectable(
                        std::format("##ble_table_selectable{:d}", i).c_str(),
                        m_selectedRow == i,
                        ImGuiSelectableFlags_SpanAllColumns |
                            ImGuiSelectableFlags_AllowOverlap)) {
                    m_selectedRow = i;
                }
            }

            i++;
        }

        ImGui::EndTable();
    }

    const char* scan_text =
        (m_ble.isScanning() == false ? "Scan for Devices" : "Stop Scanning");

    if (ImGui::Button(scan_text)) {
        if (m_ble.isScanning() == false) {
            m_ble.startScan();
        } else {
            m_ble.stopScan();
        }
    }
    ImGui::SameLine();
    if (m_selectedRow == -1) {
        ImGui::BeginDisabled();
    }

    const char* connect_text = (m_pConnected.peripheral.initialized() &&
                                m_pConnected.peripheral.is_connected())
                                   ? "Disconnect"
                                   : "Connect";

    if (ImGui::Button(connect_text)) {
        auto devices = m_ble.getDevices();
        if (m_selectedRow >= 0 && m_selectedRow < devices.size()) {
            auto p = devices[m_selectedRow].peripheral;
            if (m_pConnected.peripheral.initialized() &&
                m_pConnected.peripheral.is_connected()) {
                m_pConnected.peripheral.disconnect();
            } else {
                m_ble.connect(devices[m_selectedRow].peripheral.address());
                m_pConnected = devices[m_selectedRow];
            }
        }
    }
    if (m_selectedRow == -1) {
        ImGui::EndDisabled();
    }

    ImGui::End();

    // Bluetooth Connected Device
    ImGui::Begin("Connection Status");

    ImGui::Text("Connection Status:");
    if (m_pConnected.peripheral.initialized() &&
        m_pConnected.peripheral.is_connected()) {
        ImGui::Text("Connected to %s",
                    m_pConnected.peripheral.identifier().c_str());
    } else {
        ImGui::Text("Not connected to any device.");
    }

    if (m_pConnected.peripheral.initialized()) {
        for (auto& service : m_pConnected.peripheral.services()) {
            ImGui::Separator();
            ImGui::Text("Service: %s", service.uuid().c_str());
            for (auto& characteristic : service.characteristics()) {
                ImGui::Text("  Characteristic: %s",
                            characteristic.uuid().c_str());
                ImGui::Text("    Properties:");
                if (characteristic.can_read()) {
                    ImGui::SameLine();
                    ImGui::Text("Read");
                }
                if (characteristic.can_write_request()) {
                    ImGui::SameLine();
                    ImGui::Text("Write Request");
                }
                if (characteristic.can_write_command()) {
                    ImGui::SameLine();
                    ImGui::Text("Write Command");
                }
                if (characteristic.can_notify()) {
                    ImGui::SameLine();
                    ImGui::Text("Notify");
                }
                if (characteristic.can_indicate()) {
                    ImGui::SameLine();
                    ImGui::Text("Indicate");
                }
                ImGui::NewLine();
            }
        }
    }

    ImGui::End();

}