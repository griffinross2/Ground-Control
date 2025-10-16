#pragma once

#include "app_window.h"

#include <vector>
#include <memory>
#include <type_traits>

#include <GLFW/glfw3.h>

class Application {
public:
    Application();
    ~Application();

    int Init();
    int Run();
    void Shutdown();
    GLFWwindow* GetWindow() const { return m_window; }

    template <typename T>
        requires std::is_base_of_v<AppWindow, T>
    void PushLayer() {
        m_layers.push_back(std::make_unique<T>());
    }

    float m_uiScale = 1.0f;
private:
    GLFWwindow* m_window;
    std::vector<std::unique_ptr<AppWindow>> m_layers;
};

extern Application* g_appInstance;