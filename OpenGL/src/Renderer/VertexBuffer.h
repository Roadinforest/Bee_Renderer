#pragma once
class VertexBuffer
{
public:
	VertexBuffer(const void* buffer,const unsigned size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RenderereId;
};

