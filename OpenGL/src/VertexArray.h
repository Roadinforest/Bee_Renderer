#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
/* Include the vertex "data" without index */
{
public:
	VertexArray();
	~VertexArray();

	void Bind()const;
	void Unbind()const;
	inline unsigned int GetRendererID() { return m_RendererId; }
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout layout);

private:
	unsigned int m_RendererId;
	
};

