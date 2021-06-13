#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Utils/Utils.h"
#include <iostream>

typedef unsigned int uint;

const char* vertSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

const char* fragSource0 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}";

const char* fragSource1 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}";

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_Q))
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int run()
{
	const int width = 600, height = 600;

	GLFWwindow *window = createGLFWWindow(width, height);

	uint shaderProgram0 = compileShaderProgram(vertSource, fragSource0);
	uint shaderProgram1 = compileShaderProgram(vertSource, fragSource1);

	float vertices[] = {
		-0.75, -0.25, 0.0,
		-0.5, 0.25, 0.0f,
		-0.25, -0.25, 0.0f,
		0.25, -0.25, 0.0,
		0.5, 0.25, 0.0f,
		0.75, -0.25, 0.0f,
	};

	uint VAO0, VAO1, VBO0, VBO1;;

	glGenVertexArrays(1, &VAO0);
	glGenBuffers(1, &VBO0);

	glBindVertexArray(VAO0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);

	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices + 9, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0, 0, 1.0f, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram0);
		glBindVertexArray(VAO0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO0);
	glDeleteVertexArrays(1, &VAO1);
	glDeleteBuffers(1, &VBO0);
	glDeleteBuffers(1, &VBO1);
	glDeleteProgram(shaderProgram0);
	glDeleteProgram(shaderProgram1);

	glfwTerminate();
	return 0;
}