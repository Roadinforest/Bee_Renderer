#pragma once
class IndexBuffer
{
public:
	IndexBuffer(const void* buffer,const unsigned int count);
	~IndexBuffer();

	void Bind();
	void Unbind();

private:
	unsigned int m_RenderereId;
	unsigned int m_Count;
};

