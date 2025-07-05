#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "examples.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath)
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
static unsigned int CompileShader(unsigned int type ,const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); // This will be danger if we the source string is invalid or free later
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cerr << " Failed to compile " <<
			(type==GL_VERTEX_SHADER ? "vertex" : "fragment") 
			<< " shader! " << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
	 
}

/* It is basically create a vertex shader and fragment shader using the source text */
static unsigned int CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

/* Just set the vertex and draw it without using buffer*/
void drawSimpleTriangle()
{
	glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, +0.0f);
		glVertex2f(+0.5f, -0.5f);
		glVertex2f(-0.5f, +0.5f);
	glEnd();
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cerr << " Error create glfw window " << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* In the GLEW doc said that the glewInit() should be called after the context be set */
	if (glewInit() != GLEW_OK)
		std::cerr << " Error init glew." << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;


	/* ---------- Set the OpenGL buffer ---------- */
	float pos[6] = {
		-0.5f, +0.0f,
		+0.5f, -0.5f,
		-0.5f, +0.5f
	};

	/* Create a OpenGL Buffer NAME */
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	/* Choose which buffer to use right now */
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	/* Create a OpenGL Buffer object */

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);

	/* -------------------------------------------- */

	/* Set the vertex attribute */
	unsigned int AttribIndex = 0;
	glEnableVertexAttribArray(AttribIndex); /* You can enable it at any line, not necessary to be front of glVertexAttribPointer */
	glVertexAttribPointer(AttribIndex, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);

	/* ---------- Create a program with two shaders ---------- */

	ShaderProgramSource ShaderSource = ParseShader("res/shaders/Basic.shader");
	std::cout << "Vertex Shader" << std::endl;
	std::cout << ShaderSource.VertexSource << std::endl;
	std::cout << "Fragment Shader" << std::endl;
	std::cout << ShaderSource.FragmentSource<< std::endl;


	unsigned int program = CreateShaderProgram(ShaderSource.VertexSource, ShaderSource.FragmentSource);
	glUseProgram(program);

	/* --------------------------------------------------------- */

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES,0,3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(program);

	glfwTerminate();
	return 0;
}