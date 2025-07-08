#pragma once
class IndexBuffer
{
public:
	IndexBuffer(const void* buffer,const unsigned int count);
	~IndexBuffer();

	void Bind()const;
	void Unbind()const;
	inline unsigned int GetCount()const { return m_Count; }

private:
	unsigned int m_RenderereId;
	unsigned int m_Count;
};

