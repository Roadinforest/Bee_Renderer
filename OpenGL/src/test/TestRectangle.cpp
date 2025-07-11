#include "TestRectangle.h"
#include "gl/glew.h"

#include "VertexBufferLayout.h"

test::TestRectangle::TestRectangle()
{
	float pos[] = {
		 0.0f,      0.0f,
		1000.0f,    0.0f,
		1000.0f, 1000.0f,
		   0.0f, 1000.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(pos, 4 * 2 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2); /* Push the position*/
	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	shader = std::make_unique<Shader>("res/shaders/Simple.shader");
	shader->Bind();
}

test::TestRectangle::~TestRectangle()
{

}

void test::TestRectangle::OnUpdate(float deltaTime /*= 0*/)
{

}

void test::TestRectangle::OnRender()
{
	Renderer renderer;
	renderer.Draw(*m_VAO, *m_IndexBuffer, *shader);
}

void test::TestRectangle::OnImGuiRender()
{
}
