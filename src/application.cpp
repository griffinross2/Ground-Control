#include "application.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Application* g_appInstance;

int imgui_init(GLFWwindow*& window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    io.Fonts->AddFontFromFileTTF("fonts/Roboto/static/Roboto-Regular.ttf");

    return 0;
}

Application::Application() {
    g_appInstance = this;
}

Application::~Application() {
    g_appInstance = nullptr;
}

int Application::Init() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    if (!glfwInit())
        return -1;

    m_window =
        glfwCreateWindow(1920, 1080, "Ground Control v0.1", nullptr, nullptr);

    if (!m_window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_window);
    
    imgui_init(m_window);

    glfwSwapInterval(1);  // vsync

    float xscale, yscale;
    glfwGetWindowContentScale(m_window, &xscale, &yscale);
    m_uiScale = (xscale + yscale) / 2.0f;

    // ImGui::GetStyle().ScaleAllSizes(m_uiScale);
    ImGui::GetStyle().FontScaleDpi = m_uiScale;

    return 0;
}

int Application::Run() {
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        // Update
        for (auto& layer : m_layers) {
            layer->Update();
        }
        
        ImGui::NewFrame();

        // Render
        for (auto& layer : m_layers) {
            layer->Render();
        }

        ImGui::Render();

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
    }

    return 0;
}

void Application::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}