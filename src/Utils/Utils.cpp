#include <glad/glad.h>
#include <iostream>
#include "Utils.h"

unsigned int compileShaderProgram(const char *vert, const char *frag)
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vert, nullptr);
    glCompileShader(vertexShader);

    int compileSuccess;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileSuccess);

    if (!compileSuccess)
    {
        char info[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, info);
        std::cout << "VERTEX SHADER COMPILATION FAILURE:\n" << info << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &frag, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileSuccess);
    if (!compileSuccess)
    {
        char info[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, info);
        std::cout << "FRAGMENT SHADER COMPILATION FAILURE:\n" << info << std::endl;
    }

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetShaderiv(program, GL_COMPILE_STATUS, &compileSuccess);
    if (!compileSuccess)
    {
        char info[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, info);
        std::cout << "SHADER PROGRAM COMPILATION FAILURE:\n" << info << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow *createGLFWWindow(int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // compat versions
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // no legacy functions
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // needed for mac support, might as well just leave in windows code

    GLFWwindow* window = glfwCreateWindow(width, height, "GLFW Window", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // initialize glad with correct func pointer
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    return window;
}

