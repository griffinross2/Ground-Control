#include "data_views/data_table.h"

DataTable::DataTable(std::array<std::string, N_COLS> columnNames)
    : m_columnNames(columnNames), m_data({}) {
}

void DataTable::HighlightRow(int index) {
	// TODO
}

void DataTable::AddRow(std::array<float, N_COLS> rowdata) {
    m_data.push_back(rowdata);
}

void DataTable::RemoveRow(int index) {
    m_data.erase(m_data.begin() + index);
}

std::array<float, N_COLS> DataTable::GetRow(int index) {
    if (index > m_data.size() - 1 || index < 0) {
        std::array<float, N_COLS> out{-1.f, -1.f, -1.f};
        return out;
    }

    return m_data[index];
}

std::vector<float> DataTable::GetColumn(int index) {
	std::vector<float> out = {};

	if (index > N_COLS - 1 || index < 0) 
		return out;

	for (const auto& row : m_data)
		out.push_back(row[index]);

	return out;
}

std::string DataTable::GetHeader(int index) {
	std::string out = "";

	if (index > N_COLS - 1 || index < 0) 
		return out;

	out = m_columnNames[index];
	return out;
}

void DataTable::Clear() {
    m_data.clear();
}

void DataTable::Render() {
	float height = ImGui::GetWindowSize().y - 800.0f; // accounting for bottom buttons. TODO: change 600 to a more sensible number

	if (ImGui::BeginTable("Data", N_COLS, ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY, ImVec2(0.0f, height))) {
		for (const auto& name : m_columnNames) {
			ImGui::TableSetupColumn(name.c_str());
		}

		ImGui::TableHeadersRow();

		for (const auto& entry : m_data) {
			ImGui::TableNextRow();

			for (int i = 0; i < N_COLS; i++) {
				ImGui::TableSetColumnIndex(i);
				ImGui::Text(std::to_string(entry[i]).c_str());
			}
		}

		ImGui::EndTable();
	}
}
