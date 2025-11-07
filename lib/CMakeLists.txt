target_include_directories(${PROJECT_NAME} PRIVATE
    imgui
    imgui/backends
)

target_sources(${PROJECT_NAME} PRIVATE
	implot/implot.cpp
	implot/implot_items.cpp
	imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/backends/imgui_impl_glfw.cpp
)
