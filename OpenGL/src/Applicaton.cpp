#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "examples.h"

/* Just set the vertex and draw it without using buffer*/
void drawSimpleTriangle()
{
	glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, +0.0f);
		glVertex2f(+0.5f, -0.5f);
		glVertex2f(-0.5f, +0.5f);
	glEnd();
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cerr << " Error create glfw window " << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* In the GLEW doc said that the glewInit() should be called after the context be set */
	if (glewInit() != GLEW_OK)
		std::cerr << " Error init glew." << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;


	float pos[6] = {
		-0.5f, +0.0f,
		+0.5f, -0.5f,
		-0.5f, +0.5f
	};

	/* Create a OpenGL Buffer NAME */
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	/* Choose which buffer to use right now */
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	/* Create a OpenGL Buffer object */

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);

	/* Set the vertex attribute */
	glEnableVertexAttribArray(0); /* You can enable it at any line, not necessary to be front of glVertexAttribPointer */
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES,0,3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}