#pragma once

#include "Test.h"

#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/IndexBuffer.h" 

#include "Renderer/VertexBuffer.h"
#include "Renderer/Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>


namespace test
{
	class TestRectangle :public Test
	{
	public:
		TestRectangle();
		~TestRectangle();
		void OnUpdate(float deltaTime = 0)override;
		void OnRender()override;
		void OnImGuiRender()override;

	private:
		std::unique_ptr<Shader> shader;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer; 
		std::unique_ptr<Texture> texture; 
	};
}
