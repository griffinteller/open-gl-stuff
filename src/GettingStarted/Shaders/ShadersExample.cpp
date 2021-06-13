#include <Utils/Shader.h>

int run()
{
    const int WIDTH = 600, HEIGHT = 600;
    GLFWwindow *window = createGLFWWindow(WIDTH, HEIGHT);

    const float vertices[] {
        -0.5, -0.5, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0, 1.0, 0.0,
        0.5, -0.5, 0.0f, 0.0, 0.0, 1.0
    };

    Shader shader ("C:/Users/griff/CLionProjects/LearnOpenGL/src/GettingStarted/Shaders/color.vert",
                   "C:/Users/griff/CLionProjects/LearnOpenGL/src/GettingStarted/Shaders/color.frag");

    uint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 6, nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 6, (void *) (sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}