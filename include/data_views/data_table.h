#pragma once

#include <array>
#include <string>
#include <string_view>
#include <vector>

#include "imgui.h"

constexpr const int N_COLS = 3;

class DataTable {
private:
    std::array<std::string, N_COLS> m_columnNames;
    std::vector<std::array<float, N_COLS>> m_data;
	ImVec2 m_displayDim;
    void HighlightRow(int index);

public:
    DataTable(std::array<std::string, N_COLS> columnNames);

    void AddRow(std::array<float, N_COLS> rowdata);
    void RemoveRow(int index);
    std::array<float, N_COLS> GetRow(int index);
	std::vector<float> GetColumn(int index);
	std::string GetHeader(int index);
	void SetDisplayDimensions(ImVec2 dim);
	ImVec2 GetDisplayDimensions();
    void Clear();
    void Render();
};
