#pragma once

#include <vector>

#include "plot.h"

class LinePlot : public Plot {
	private:
		// DataTable* m_data;
		int m_xIndex;
		std::vector<int> m_yIndices;

	public:
		LinePlot();
		LinePlot(std::string xLabel, std::string yLabel, std::string title);
		void LoadData(DataTable& data);
		void SetXIndex(int index);
		void SetYIndices(std::vector<int> indices);
		void Render();
};
