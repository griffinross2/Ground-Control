#include "flight_window.h"

#include "imgui.h"

FlightWindow::FlightWindow() : m_data({"Timestamp", "Column A", "Column B"}) {
	m_data.AddRow({1.0f, 2.0f, 3.0f});
}

FlightWindow::~FlightWindow() {}

void FlightWindow::Update() {}

void FlightWindow::Render() {
    ImGui::Text("Flight page.");
	m_data.Render();
}
