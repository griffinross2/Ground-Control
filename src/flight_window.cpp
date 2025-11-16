#include "flight_window.h"

#include "imgui.h"

FlightWindow::FlightWindow() : m_data({"Timestamp", "Column A", "Column B"}), m_plot("Timestamp", "Column A", "Figure Title") {
	for (float i = 0.0f; i < 1000.0f; i++) { // Sample data
		m_data.AddRow({i, i + 1, (i + 1) * (i + 1)});
	}

	m_plot.LoadData(m_data);
	m_plot.SetXIndex(0);
	m_plot.SetYIndices({1, 2});
}

FlightWindow::~FlightWindow() {}

void FlightWindow::Update() {}

void FlightWindow::Render() {
    ImGui::Text("Flight page.");

	ImVec2 dims(ImGui::GetWindowSize().x / 2.0f, ImGui::GetWindowSize().y - 800.0f);

	m_data.SetDisplayDimensions(dims);

	m_data.Render();
	ImGui::SameLine();
	m_plot.Render();
}
