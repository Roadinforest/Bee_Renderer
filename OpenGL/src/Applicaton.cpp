#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"


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

	/* Spefify the OpenGL version */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello OpenGL", NULL, NULL);
	if (!window)
	{
		std::cerr << " Error create glfw window " << std::endl;
		GLCall(glfwTerminate());
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);	/* Should synchronize with V-Sync */

	/* In the GLEW doc said that the glewInit() should be called after the context be set */
	if (glewInit() != GLEW_OK)
		std::cerr << " Error init glew." << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;


	/* Because the destructor of VertexBuffer and IndexBuffer cannot be performed normally 
	 * after the glDeleteProgram(). We should use the {} to let their destructor be called 
	 * before. */
	{
		/* ---------- Set the OpenGL buffer : vertex buffer and indice buffer ---------- */
		float pos[] = {
			-0.5f, -0.5f,
			+0.5f, -0.5f,
			+0.5f, +0.5f,
			-0.5f, +0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		/* --- Use the vertex array object without binding ---*/
		VertexArray va;
		/* ------------------------------------------------- */


		/* --- Set the vertex buffer and vertexattribute --- */
		VertexBuffer vb(&pos, 8 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		/* Each operation of va will use Bind() first, so you don't have to Bind() before
		 * the operation./
		/* ------------------------------------------------- */

		/* --- Create indice buffer --- */
		IndexBuffer ib(&indices, 6);
		/* -----------------------------*/


		/* ---------- Create a program with two shaders ---------- */
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		float r = 0.0f;
		float increment = 0.01f;
		shader.SetUniform4f("u_Color", r, 0.3f, 0.3f, 0.3f);
		/* ----------------------------------------------------------- */

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.3f, 0.3f);

			if (r > 1.0f || r < 0.0f)
				increment = -increment;

			r += increment;

			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
			
			va.Bind();  /* Bind vertex array */
			ib.Bind();  /* Bind index  array */

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}
	}/* The destrutor will be called at this place. */
	glfwTerminate();
	return 0;
}