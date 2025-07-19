#include "TestTexture2D.h"

#include "Renderer/VertexBufferLayout.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

namespace test
{
	TestTexture2D::TestTexture2D()
		:
		translationA(glm::vec3(0,0,0)),translationB(glm::vec3(300,0,0))
	{
		float pos[] = {
			   0.0f,    0.0f, 0.0f, 0.0f,
			1000.0f,    0.0f, 1.0f, 0.0f,
			1000.0f, 1000.0f, 1.0f, 1.0f,
			   0.0f, 1000.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		texture = std::make_unique<Texture>("res/textures/Dream_chaser.png");

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique< VertexBuffer>(pos, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2); /* Push the position*/
		layout.Push<float>(2); /* Push the texture position */
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);


		shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		shader->Bind();
		shader->SetUniform1i("u_Texture", 0); /* Set the slot of the texture. */

		proj = glm::ortho(0.0f, 1500.0f, 0.0f, 1500.0f, -100.0f, 100.0f);   /* Ortho projection matrix. */
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));      /* View matrix. */
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));      /* Model matrix. */
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime /*= 0*/)
	{
	}

	void TestTexture2D::OnRender()
	{
		Renderer renderer;
		texture->Bind();

		{
			glm::mat4 modelA = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvpA = proj * view * modelA;

			shader->Bind();
			shader->SetUniformMat4f("u_MVP", mvpA);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *shader);
		}

		{
			glm::mat4 modelB = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvpB = proj * view * modelB;

			shader->Bind();
			shader->SetUniformMat4f("u_MVP", mvpB);

			renderer.Draw(*m_VAO, *m_IndexBuffer, *shader);
		}

	}

	void TestTexture2D::OnImGuiRender()
	{
		{
			ImGui::SliderFloat("TranslationA X", &translationA.x, 0.0f, 1000.0f);
			ImGui::SliderFloat("TranslationA Y", &translationA.y, 0.0f, 1000.0f);
			ImGui::SliderFloat("TranslationA Z", &translationA.z, -150.0f, 150.0f);
		}

		{
			ImGui::SliderFloat("TranslationB X", &translationB.x, 0.0f, 1000.0f);
			ImGui::SliderFloat("TranslationB Y", &translationB.y, 0.0f, 1000.0f);
			ImGui::SliderFloat("TranslationB Z", &translationB.z, -150.0f, 150.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
	}

}
