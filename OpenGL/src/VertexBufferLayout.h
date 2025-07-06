#pragma once

#include "GL/glew.h"
#include "Shader.h"
#include <vector>


struct VertexBufferElement
{
	unsigned type;    /* Correspond to GL_INT etc */
	unsigned count;		
	unsigned char normalized;   /* Do you want the OpenGL do the normailzation job for you. */
	static unsigned char GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case(GL_FLOAT):
				return 4;
			case(GL_UNSIGNED_INT):
				return 4;
			case(GL_BYTE):
				return 1;
		}

		ASSERT(false);
		return 0;
	}
};


class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride = 0;

public:
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE});
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE});
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<char>(unsigned int count)
	{
		m_Elements.push_back({ GL_BYTE,count,GL_FALSE});
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const {	return m_Elements; }

	inline unsigned int GetStride() const { return m_Stride; }
};
