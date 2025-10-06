#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <format>

#include <bluetooth.h>

constexpr const int TEXT_WIDTH_PADDING = 10;  // pixels
constexpr const float TABLE_MAX_HEIGHT = 350.0f;

int imgui_init(GLFWwindow*& window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    io.Fonts->AddFontFromFileTTF("fonts/Roboto/static/Roboto-Regular.ttf");

    return 0;
}

void center_text(float text_width) {
    float window_width = ImGui::GetWindowSize().x;

    ImGui::SetCursorPosX((window_width - text_width) / 2.0f);
}

int main(int argc, char** argv) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window =
        glfwCreateWindow(1920, 1080, "Ground Control v0.1", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);  // vsync

    imgui_init(window);

    bool bt_enabled = true;
    BluetoothManager ble;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Draw FPS in the top-left corner
        ImGui::GetBackgroundDrawList()->AddText(
            ImGui::GetFont(), 16, ImVec2(10.0f, 10.0f),
            IM_COL32(255, 255, 255, 255),
            std::format("FPS: {:.2f}", ImGui::GetIO().Framerate).c_str());

        if (!ble.isBluetoothEnabled() && bt_enabled) {
            const char* text =
                "Warning: Bluetooth is not enabled on your device.\nMost "
                "functions will not work if Bluetooth is not enabled.";

            ImGui::SetNextWindowSize(
                ImVec2(static_cast<int>(ImGui::CalcTextSize(text).x) +
                           TEXT_WIDTH_PADDING,
                       120));
            ImGui::Begin("Warning", &bt_enabled, ImGuiWindowFlags_NoResize);

            ImGui::Text(text);

            center_text(ImGui::CalcTextSize("OK").x + 150.0f);

            if (ImGui::Button("OK", ImVec2(150.0f, 0.0f))) {
                bt_enabled = false;
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

            for (size_t i = 0; auto& p : ble.getDevices()) {
                if (p.name.length() > 0) {
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(p.name.c_str());

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text(p.address.c_str());

                    ImGui::TableSetColumnIndex(2);
                    ImGui::BeginDisabled();
                    ImGui::SetNextItemWidth(-1);
                    ImGui::SliderInt(std::format("##rssi{:d}", i).c_str(),
                                     &p.rssi, -100, 0,
                                     std::format("{:2d} dBm", p.rssi).c_str(),
                                     ImGuiSliderFlags_NoInput);
                    ImGui::EndDisabled();
                }

                i++;
            }

            ImGui::EndTable();
        }

        const char* scan_text =
            (ble.isScanning() == false ? "Scan for Devices" : "Stop Scanning");

        if (ImGui::Button(scan_text)) {
            if (ble.isScanning() == false) {
                ble.startScan();
            } else {
                ble.stopScan();
            }
        }

        ImGui::End();

        ImGui::Render();

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
