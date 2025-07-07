#include "VertexArray.h"
#include "Renderer.h"
#include "GL/glew.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererId));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1,&m_RendererId));
}


void VertexArray::Bind()
{
	GLCall(glBindVertexArray(m_RendererId));
}

void VertexArray::Unbind()
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout layout)
{
	Bind();
	vb.Bind();  /* Bind the vertex buffer, then set its layout. */
	const auto& elements = layout.GetElements();
	unsigned offset = 0;
	for (unsigned i = 0; i < elements.size(); i++)
	{
		const auto& entity = elements[i];
		GLCall(glEnableVertexAttribArray(i)); 
		GLCall(glVertexAttribPointer(i, entity.count, entity.type, entity.normalized , layout.GetStride(), (const void*)offset));
		offset += VertexBufferElement::GetSizeOfType(entity.type) * entity.count;
	}

}
