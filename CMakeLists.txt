cmake_minimum_required(VERSION 3.20)
project(program)
set(CMAKE_CXX_STANDARD 17)
set(TARGET program)

#add_compile_definitions(GLEW_STATIC)

add_executable(${TARGET} main.cpp)
# glfw3 dependents on X11 for window creation
target_link_libraries(${TARGET} glfw3 X11 OpenGL GLEW)
