#pragma once

#include <string>
#include <memory>
#include "imgui.h"
#include "implot.h"

#include "data_table.h"

class Plot {
	protected:
		std::string m_xLabel, m_yLabel, m_title;
		DataTable* m_data; // This is probably a bad idea but I can't think of another way to do it; I want each plot to be able to borrow data from a DataTable object, wwhich for now lives on the stack so we shouldn't have to worry about freeing this pointer unless we decide to heap allocate DataTables to save stack memory
	
	public:
		Plot() : m_xLabel(""), m_yLabel(""), m_title(""), m_data(nullptr) {}
		Plot(std::string xLabel, std::string yLabel, std::string title) : m_xLabel(xLabel), m_yLabel(yLabel), m_title(title), m_data(nullptr) {}
		virtual void Render() {}
};
