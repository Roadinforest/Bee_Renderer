#pragma once

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

class VertexArray
/* Include the vertex "data" without index */
{
public:
	VertexArray();
	~VertexArray();

	void Bind();
	void Unbind();
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout layout);

private:
	unsigned int m_RendererId;
	
};

