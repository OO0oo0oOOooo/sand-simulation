cmake_minimum_required(VERSION 3.20)

project(imgui)
add_library(imgui STATIC
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC .)
target_link_libraries(imgui PRIVATE glfw)
