#pragma once

#include "test/Test.h"

#include "Shader.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h" 

#include "VertexBuffer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>

namespace test
{
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime = 0) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<Shader> shader;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer; 
		std::unique_ptr<Texture> texture; 

		glm::vec3 translationA;
		glm::vec3 translationB;

		glm::mat4 proj, view, model;
	};
}
