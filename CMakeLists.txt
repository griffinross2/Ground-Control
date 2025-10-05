cmake_minimum_required(VERSION 3.26)
project(Ground-Control)

include(FetchContent)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif(UNIX)

# Executable
add_executable(${PROJECT_NAME})

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

FetchContent_GetProperties(glfw
    POPULATED glfw_POPULATED
    SOURCE_DIR glfw_SOURCE_DIR
    BINARY_DIR glfw_BINARY_DIR
)

if(glfw_POPULATED)
    message(STATUS "glfw has been populated.")
    message(STATUS "Source directory: ${glfw_SOURCE_DIR}")
    message(STATUS "Binary directory: ${glfw_BINARY_DIR}")
endif()

# IMGUI
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends)
target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/backends/imgui_impl_glfw.cpp)

# SimpleBLE
add_subdirectory("./lib/simpleble/simpleble" ${CMAKE_BINARY_DIR}/simpleble)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    opengl32
	simpleble::simpleble
)

# Headers
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Source files
add_subdirectory(src)
