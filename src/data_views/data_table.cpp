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

void DataTable::Clear() {
    m_data.clear();
}

void DataTable::Render() {
	if (ImGui::BeginTable("Data", N_COLS, ImGuiTableFlags_Borders)) {
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
