#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"


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
	window = glfwCreateWindow(1280, 960, "Hello OpenGL", NULL, NULL);
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
			 0.0f,      0.0f, 0.0f, 0.0f,
		    1000.0f,    0.0f, 1.0f, 0.0f,
			1000.0f, 1000.0f, 1.0f, 1.0f,
			   0.0f, 1000.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		glm::mat4 proj 	= glm::ortho(0.0f, 1500.0f, 0.0f, 1500.0f, -100.0f, 100.0f);   /* Ortho projection matrix. */
		glm::mat4 view 	= glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));      /* View matrix. */
		glm::mat4 model	= glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));      /* Model matrix. */

		glm::mat4 mvp = proj * view * model;


		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		/* --- Use the vertex array object without binding ---*/
		VertexArray va;
		/* ------------------------------------------------- */

		/* --- Set the vertex buffer and vertexattribute --- */
		VertexBuffer vb(&pos, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2); /* Push the position*/
		layout.Push<float>(2); /* Push the texture position */
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
		shader.SetUniform4f("u_Color", r, 0.3f, 0.3f, 0.3f); // Should always be called after Bind() function
		shader.SetUniformMat4f("u_MVP", mvp); // Should always be called after Bind() function
		/* ----------------------------------------------------------- */

		va.Unbind();
		vb.Unbind();
		ib.Unbind();

		Renderer renderer;

		Texture texture("res/textures/Dream_chaser.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0); /* Set the slot of the texture. */
		shader.Unbind();

		// Setup ImGui binding
		ImGui::CreateContext();
		//ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		glm::vec3 translationA(0, 0, 0);
		glm::vec3 translationB(700, 0, 0);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();
			ImGui_ImplGlfwGL3_NewFrame();

			texture.Bind();

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);      /* Model matrix. */
				glm::mat4 mvp = proj * view * model;
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp); // Should always be called after Bind() function
				renderer.Draw(va, ib, shader);
			}

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);      /* Model matrix. */
				glm::mat4 mvp = proj * view * model;
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp); // Should always be called after Bind() function
				renderer.Draw(va, ib, shader);
			}

			{
				ImGui::SliderFloat("TranslationA X", &translationA.x,    0.0f, 1000.0f); 
				ImGui::SliderFloat("TranslationA Y", &translationA.y,    0.0f, 1000.0f); 
				ImGui::SliderFloat("TranslationA Z", &translationA.z, -150.0f, 150.0f); 
			}

			{
				ImGui::SliderFloat("TranslationB X", &translationB.x,    0.0f, 1000.0f); 
				ImGui::SliderFloat("TranslationB Y", &translationB.y,    0.0f, 1000.0f); 
				ImGui::SliderFloat("TranslationB Z", &translationB.z, -150.0f, 150.0f); 
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}
	}/* Out destrutors will be called at this bracket. */
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}