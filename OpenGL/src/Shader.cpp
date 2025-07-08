#include "Shader.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"


Shader::Shader(const std::string& filePath)
{
	ShaderProgramSource ShaderSource = ParseShader(filePath);
	m_RendererId = CreateShaderProgram(ShaderSource.VertexSource, ShaderSource.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererId));
}

void Shader::Bind()const
{
	GLCall(glUseProgram(m_RendererId));
}

void Shader::Unbind()const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	GLCall(unsigned int location = glGetUniformLocation(m_RendererId, name.c_str()););
	if (location == -1)
	{
		std::cout << "Warning uniform: " << name << " 'doesn't exist! " << std::endl;
	}
	/* Install the location unconditional. */
	m_UniformLocationCache[name] = location;
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::fstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(),ss[1].str() };
}

/* The kernel combination function */
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); // This will be danger if we the source string is invalid or free later
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cerr << " Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader! " << std::endl;
		std::cout << message << std::endl;

		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;

}

unsigned int Shader::CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}
