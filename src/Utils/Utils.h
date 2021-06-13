#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef unsigned int uint;

unsigned int compileShaderProgram(const char *vert, const char *frag);

GLFWwindow *createGLFWWindow(int width, int height);

