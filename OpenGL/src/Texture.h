#pragma once
#include <string>

class Texture
{
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot = 0)const;
	void Unbind()const;

private:
	unsigned int m_RendererId = 0;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer = nullptr;
	int m_Width = 0;
	int m_Height = 0 ;
    int m_BPP = 0;
};

