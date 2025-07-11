#include "Renderer.h"

#include "GL/glew.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "[OpenGL Error] (" << error << "): " << function << 
			" " << file <<":"<<line<<std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)const
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
