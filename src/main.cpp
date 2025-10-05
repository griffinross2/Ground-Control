#include <simpleble/SimpleBLE.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

constexpr const int TEXT_WIDTH_PADDING = 10; // pixels
constexpr const float TABLE_MAX_HEIGHT = 350.0f;

int imgui_init(GLFWwindow*& window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	io.Fonts->AddFontFromFileTTF("fonts/Roboto/static/Roboto-Regular.ttf");

	return 0;
}

void center_text(float text_width)
{
	float window_width = ImGui::GetWindowSize().x;

	ImGui::SetCursorPosX((window_width - text_width) / 2.0f);
}

int main(int argc, char** argv)
{
	bool bt_enabled = true;
	bool bt_scanning = false;
	bool scan_started = false;
	SimpleBLE::Adapter adapter;
	std::vector<SimpleBLE::Peripheral> pers;
	//std::vector<std::pair<const char*, const char*>> per_ids;

	if (SimpleBLE::Adapter::bluetooth_enabled())
	{
		adapter = SimpleBLE::Adapter::get_adapters()[0];

		// TODO: fix this because a data race happens by the looks of it
		/*
		adapter.set_callback_on_scan_updated([&](SimpleBLE::Peripheral p) {
			// filters out useless devices
			if (p.identifier().length() > 0)
			{
				per_ids.push_back(std::pair(p.identifier().c_str(), p.address().c_str()));
			}
		});
		*/
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1920, 1080, "Ground Control v0.1", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); // vsync

	imgui_init(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// SimpleBLE
		if (bt_scanning && !scan_started)
		{
			scan_started = true;
			adapter.scan_start();
		}
		else if (!bt_scanning && scan_started)
		{
			adapter.scan_stop();
			scan_started = false;
			pers = adapter.scan_get_results();
		}

		// IMGUI rendering
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		if (!SimpleBLE::Adapter::bluetooth_enabled() && bt_enabled)
		{
			const char* text = "Warning: Bluetooth is not enabled on your device.\nMost functions will not work if Bluetooth is not enabled.";

			ImGui::SetNextWindowSize(ImVec2(static_cast<int>(ImGui::CalcTextSize(text).x) + TEXT_WIDTH_PADDING, 120));
			ImGui::Begin("Warning", &bt_enabled, ImGuiWindowFlags_NoResize);

			ImGui::Text(text);

			center_text(ImGui::CalcTextSize("OK").x + 150.0f);

			if (ImGui::Button("OK", ImVec2(150.0f, 0.0f)))
			{
				bt_enabled = false;
			}

			ImGui::End();
		}

		ImGui::Begin("Bluetooth Devices");
		ImGui::Text("Select a device to pair with.");

		if (ImGui::BeginTable("main", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY, ImVec2(0.0f, TABLE_MAX_HEIGHT)))
		{
			ImGui::TableSetupColumn("Device Name");
			ImGui::TableSetupColumn("Bluetooth Address");

			ImGui::TableHeadersRow();

			for (auto& p : pers)
			{
				if (p.identifier().length() > 0)
				{
					ImGui::TableNextRow();

					ImGui::TableSetColumnIndex(0);
					ImGui::Text(p.identifier().c_str());

					ImGui::TableSetColumnIndex(1);
					ImGui::Text(p.address().c_str());
				}
			}

			ImGui::EndTable();
		}

		const char* scan_text = (bt_scanning == false ? "Scan for Devices" : "Stop Scanning");

		if (ImGui::Button(scan_text))
		{
			bt_scanning = !bt_scanning;
		}

		ImGui::End();
		
		ImGui::Render();

		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
