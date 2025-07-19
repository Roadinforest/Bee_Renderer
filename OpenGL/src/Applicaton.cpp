#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "test/TestClearColor.h"
#include "test/TestTexture2D.h"
#include "test/TestRectangle.h"


int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1280, 960, "Hello OpenGL", NULL, NULL);
	if (!window)
	{
		std::cerr << " Error create glfw window " << std::endl;
		GLCall(glfwTerminate());
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);	

	if (glewInit() != GLEW_OK)
		std::cerr << " Error init glew." << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;


	/* Because the destructor of VertexBuffer and IndexBuffer cannot be performed normally
	 * after the glDeleteProgram(). We should use the {} to let their destructor be called
	 * before. */
	{
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColor>("Clear Test");
		testMenu->RegisterTest<test::TestTexture2D>("2D Texture Test");
		testMenu->RegisterTest<test::TestRectangle>("Simple Triangle Test");


		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Set the default color buffer to black , if it is not overwrite by the testClear*/
			GLCall(glClearColor(0, 0, 0, 1));
			glClear(GL_COLOR_BUFFER_BIT);

			ImGui_ImplGlfwGL3_NewFrame();

			if (currentTest != nullptr)
			{
				currentTest->OnUpdate();
				currentTest->OnRender();

				ImGui::Begin("Test Menu");

				// 返回到菜单界面
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete(currentTest);
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			ImGui::Render();

			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}

		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
	}/* Out destrutors will be called at this bracket. */
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}