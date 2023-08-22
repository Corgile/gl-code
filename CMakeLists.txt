cmake_minimum_required(VERSION 3.24)
project(program)
set(CMAKE_CXX_STANDARD 17)
set(TARGET program)

add_executable(${TARGET} main.cpp)
# glfw3 dependents on X11 for window creation
target_link_libraries(${TARGET} glfw3 X11 OpenGL)
