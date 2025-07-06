#pragma once
class VertexBuffer
{
public:
	VertexBuffer(const void* buffer,const unsigned size);
	~VertexBuffer();

	void Bind();
	void Unbind();

private:
	unsigned int m_RenderereId;
};

