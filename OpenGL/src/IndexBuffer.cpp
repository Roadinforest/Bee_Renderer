#include "IndexBuffer.h"
#include "gl/glew.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const void* data,const unsigned int count)
{
	GLCall(glGenBuffers(1, &m_RenderereId));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderereId);) /* Vertex array indices */
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data , GL_STATIC_DRAW));
	m_Count = count;
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RenderereId));
}

void IndexBuffer::Bind()const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderereId));
}

void IndexBuffer::Unbind()const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 ));
}

