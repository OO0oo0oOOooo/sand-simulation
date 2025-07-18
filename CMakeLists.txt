cmake_minimum_required(VERSION 3.20)

if(WIN32)
    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "$<$<CONFIG:Debug>:MultiThreadedDebug>$<$<CONFIG:Release>:MultiThreaded>")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
    endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(sand-simulation)
set(CMAKE_CXX_STANDARD 23)

# option(GLFW_BUILD_WAYLAND "Build Wayland support" ON)
# option(GLFW_BUILD_X11 "Build X11 support" ON)

add_subdirectory("libs/glfw")
add_subdirectory("libs/glad")
add_subdirectory("libs/glm")
add_subdirectory("libs/stb_image")
add_subdirectory("libs/imgui")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable("${CMAKE_PROJECT_NAME}" "${SOURCES}")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glfw glad glm stb_image imgui)
