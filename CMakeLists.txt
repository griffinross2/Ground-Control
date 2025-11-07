cmake_minimum_required(VERSION 3.26)
project(Ground-Control)

include(FetchContent)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
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

# GLAD
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
)

FetchContent_MakeAvailable(glad)

FetchContent_GetProperties(glad
    POPULATED glad_POPULATED
    SOURCE_DIR glad_SOURCE_DIR
    BINARY_DIR glad_BINARY_DIR
)

if(glad_POPULATED)
    message(STATUS "glad has been populated.")
    message(STATUS "Source directory: ${glad_SOURCE_DIR}")
    message(STATUS "Binary directory: ${glad_BINARY_DIR}")
endif()

# Generate glad
add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
glad_add_library(glad_gl_core_45 REPRODUCIBLE API gl:core=4.5)

# SimpleBLE
FetchContent_Declare(
    simpleble
    GIT_REPOSITORY https://github.com/simpleble/simpleble.git
    GIT_TAG v0.10.3
    SOURCE_SUBDIR simpleble
)

FetchContent_MakeAvailable(simpleble)

FetchContent_GetProperties(simpleble
    POPULATED simpleble_POPULATED
    SOURCE_DIR simpleble_SOURCE_DIR
    BINARY_DIR simpleble_BINARY_DIR
)

if(simpleble_POPULATED)
    message(STATUS "simpleble has been populated.")
    message(STATUS "Source directory: ${simpleble_SOURCE_DIR}")
    message(STATUS "Binary directory: ${simpleble_BINARY_DIR}")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    opengl32
    glad_gl_core_45
    simpleble::simpleble
)

# Headers
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Source files
add_subdirectory(src)

# Included libraries
add_subdirectory(lib)

# Copy in fonts
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/fonts"
    "${CMAKE_CURRENT_BINARY_DIR}/fonts"
    COMMENT "Copying in fonts"
)
