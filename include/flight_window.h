#pragma once

#include "app_window.h"
#include "data_views/data_table.h"
#include "data_views/lineplot.h"

class FlightWindow : public AppWindow {
public:
    FlightWindow();
    ~FlightWindow();

    void Update() override;
    void Render() override;

private:
	DataTable m_data;
	LinePlot m_plot;
};
