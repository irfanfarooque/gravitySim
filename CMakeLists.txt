cmake_minimum_required(VERSION 3.10)

project(GravitySim)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source files
add_executable(a.out main.cpp glad.c)

# Include directories
target_include_directories(a.out PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find and link required libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
add_library(glad  ./glad/src/glad.c)

target_include_directories(glad PUBLIC ./glad/include)
# Link libraries to the executable
target_link_libraries(a.out PRIVATE OpenGL::GL glad glfw)
