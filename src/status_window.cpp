#include "status_window.h"

#include "imgui.h"

StatusWindow::StatusWindow() {}

StatusWindow::~StatusWindow() {}

void StatusWindow::Update() {}

void StatusWindow::Render() {
	ImGui::Begin("Rocket Status");
	
	if (ImGui::BeginTabBar("Phase")) {
		if (ImGui::BeginTabItem("Pad"))
		{
			ImGui::Text("Placeholder");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Launch"))
		{
			ImGui::Text("Placeholder");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Recovery"))
		{
			ImGui::Text("Placeholder");
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}
