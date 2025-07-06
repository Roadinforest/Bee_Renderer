#include "VertexBuffer.h"
#include "gl/glew.h"
#include "Shader.h"

VertexBuffer::VertexBuffer(const void* data,const unsigned size)
{
	GLCall(glGenBuffers(1, &m_RenderereId));
	/* Choose which buffer to use right now */
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderereId));
	/* Create a OpenGL Buffer object */
	GLCall(glBufferData(GL_ARRAY_BUFFER, size , data , GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RenderereId));
}

void VertexBuffer::Bind()const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderereId));
}

void VertexBuffer::Unbind()const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0 ));
}
