#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "examples.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))


static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}


static bool GLLogCall(const char* function,const char* file,int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "[OpenGL Error] (" << error << "): " << function << 
			" " << file <<":"<<line<<std::endl;
		return false;
	}
	return true;
}

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
			(type==GL_VERTEX_SHADER ? "vertex" : "fragment") 
			<< " shader! " << std::endl;
		std::cout << message << std::endl;

GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
	 
}

/* It is basically create a vertex shader and fragment shader using the source text */
static unsigned int CreateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	std::cout << vertexShader << std::endl;
	std::cout << fragmentShader << std::endl;
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

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

	/* Spefify the OpenGL version */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cerr << " Error create glfw window " << std::endl;
		GLCall(glfwTerminate());
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);	/* Should synchronize with V-Sync */

	/* In the GLEW doc said that the glewInit() should be called after the context be set */
	if (glewInit() != GLEW_OK)
		std::cerr << " Error init glew." << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;


	/* ---------- Set the OpenGL buffer : vertex buffer and indice buffer ---------- */
	float pos[] = {
		-0.5f, -0.5f,
		+0.5f, -0.5f,
		+0.5f, +0.5f,
		-0.5f, +0.5f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	/* Use the vertex array object */
	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	/* Create vertex buffer */
	unsigned int vertex_buffer;
	GLCall(glGenBuffers(1, &vertex_buffer));
	/* Choose which buffer to use right now */
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
	/* Create a OpenGL Buffer object */
	GLCall(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), pos, GL_STATIC_DRAW));

	/* ---------- Set the vertex attribute--------- */
	unsigned int AttribIndex = 0;
	GLCall(glEnableVertexAttribArray(AttribIndex)); /* You can enable it at any line, not necessary to be front of glVertexAttribPointer */
	GLCall(glVertexAttribPointer(AttribIndex, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0));
	/* -------------------------------------------- */

	/* Create indice buffer */
	unsigned int indice_buffer;
	GLCall(glGenBuffers(1, &indice_buffer));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice_buffer);) /* Vertex array indices */
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

	/* ------------------------------------------------------------------------------- */


	/* ---------- Create a program with two shaders ---------- */

	ShaderProgramSource ShaderSource = ParseShader("res/shaders/Basic.shader");
	unsigned int program = CreateShaderProgram(ShaderSource.VertexSource, ShaderSource.FragmentSource);
	GLCall(glUseProgram(program));


	/* The uniform variable is delivered per frame from CPU to GPU */
	GLCall(int location = glGetUniformLocation(program, "u_Color"));
	ASSERT(location != -1);
	//GLCall(glUniform4f(location, 0.9f, 0.3f, 0.8f, 1.0f));

	/* --------------------------------------------------------- */

	float r = 0.0f;
	float increment = 0.01f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

		if (r > 1.0f || r < 0.0f)
			increment = -increment;

		r += increment;

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		//GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);) /* Vertex array indices */
		GLCall(glBindVertexArray(vao));
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));



		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(window));
		/* Poll for and process events */
		GLCall(glfwPollEvents());
	}

	GLCall(glDeleteProgram(program));

	glfwTerminate();
	return 0;
}