#include "data_views/lineplot.h"

LinePlot::LinePlot() : Plot("", "", "") {}

LinePlot::LinePlot(std::string xLabel, std::string yLabel, std::string title) : Plot(xLabel, yLabel, title) {}

void LinePlot::LoadData(DataTable& data) {
	m_data = &data;
}

void LinePlot::SetXIndex(int index) {
	m_xIndex = index;
}

void LinePlot::SetYIndices(std::vector<int> indices) {
	if (indices.size() > m_yIndices.size())
		return;

	m_yIndices.clear();

	for (int i = 0; i < indices.size(); i++) {
		m_yIndices[i] = indices[i];
	}
}

void LinePlot::Render() {
	if (m_data == nullptr)
		return;

	if (ImPlot::BeginPlot(m_title.c_str())) {
		ImPlot::SetupAxes(m_xLabel.c_str(), m_yLabel.c_str());

		for (int index : m_yIndices) 
			ImPlot::PlotLine(m_data->GetHeader(index).c_str(), m_data->GetColumn(m_xIndex).data(), m_data->GetColumn(index).data(), m_data->GetColumn(index).size());

		ImPlot::EndPlot();
	}
}
