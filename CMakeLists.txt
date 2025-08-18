cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(sand-simulation)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory("engine")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable("${CMAKE_PROJECT_NAME}" "${SOURCES}")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE GeoEngine)
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")
