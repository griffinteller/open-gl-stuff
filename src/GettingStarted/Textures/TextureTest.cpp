#define STB_IMAGE_IMPLEMENTATION

#include <Utils/Shader.h>
#include "Utils/stb_image.h"

int run()
{
    const int WIDTH = 600, HEIGHT = 600;
    GLFWwindow *window = createGLFWWindow(WIDTH, HEIGHT);

    const unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    const float vertices[] = {
        // positions      // colors         // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
    };

    Shader shader ("C:/Users/griff/CLionProjects/LearnOpenGL/src/GettingStarted/Textures/rotatingTexture.vert",
                   "C:/Users/griff/CLionProjects/LearnOpenGL/src/GettingStarted/Textures/rotatingTexture.frag");

    uint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 8, (void *) (sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(float) * 8, (void *) (sizeof(float) * 6));
    glEnableVertexAttribArray(0);  // position
    glEnableVertexAttribArray(1);  // color
    glEnableVertexAttribArray(2);  // uv

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    int texWidth, texHeight, nChannels;
    unsigned char *data = stbi_load(
            "C:/Users/griff/CLionProjects/LearnOpenGL/src/GettingStarted/Textures/real.jpg",
            &texWidth, &texHeight, &nChannels, 0);

    uint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}