cmake_minimum_required(VERSION 3.20)
project(program)
set(CMAKE_CXX_STANDARD 17)
set(TARGET program)

#add_compile_definitions(GLEW_STATIC)
#@formatter:off
aux_source_directory(${PROJECT_SOURCE_DIR}/         SOURCE_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/source   SOURCE_FILES)
include_directories(${PROJECT_SOURCE_DIR}/include)
#@formatter:on

add_executable(${TARGET} main.cpp ${SOURCE_FILES})
# glfw3 dependents on X11 for window creation

target_link_libraries(${TARGET} glfw3 X11 OpenGL GLEW)
