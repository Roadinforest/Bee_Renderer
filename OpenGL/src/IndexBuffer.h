#pragma once
class IndexBuffer
{
public:
	IndexBuffer(const void* buffer,const unsigned int count);
	~IndexBuffer();

	void Bind()const;
	void Unbind()const;
	inline unsigned int GetRendererID() { return m_RendererId; }
	inline unsigned int GetCount()const { return m_Count; }

private:
	unsigned int m_RendererId;
	unsigned int m_Count;
};

