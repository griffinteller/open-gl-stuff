cmake_minimum_required(VERSION 3.19)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

link_directories(C:/opengldeps/lib-mingw-w64)

include_directories(src)
include_directories(C:/opengldeps/include)

add_executable(LearnOpenGL src/main.cpp src/glad.c src/Utils/Utils.cpp src/Utils/Shader.cpp src/GettingStarted/CoordinateSystems/3DTest.cpp)

target_link_libraries(LearnOpenGL libglfw3.a)