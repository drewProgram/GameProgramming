#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <print>

#include "Vector.h"

const unsigned int ScreenWidth = 640;
const unsigned int ScreenHeight = 480;

const char* vertexShaderSrc = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0"
;

const char* fragmentShaderSrc = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0"
;

static void HandleInput()
{

}

static void GLFWErrorCallback(int error, const char* description)
{
	std::println("ERROR {0}: {1}", error, description);
}

static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void VectorTests()
{
	std::println("Testing vector structs");

	math::Vec2 v1 = { 2.f, 10.f };
	//math::Vec2 v1 = { 3.f, 4.f };
	math::Vec2 v2 = { 10.f, 2.f };
	math::Vec2 v3;

	v3 = v1 + v2;
	std::println("Vector 1: {0}; Vector 2: {1}; Vector 1 + Vector 2: {2}", v1.ToString(), v2.ToString(), v3.ToString());

	v3 = v1 - v2;
	std::println("Vector 1: {0}; Vector 2: {1}; Vector 1 - Vector 2: {2}", v1.ToString(), v2.ToString(), v3.ToString());

	v3 = v1 * 2;
	std::println("Vector 1: {0}; Vector 1 * 2: {1}", v1.ToString(), v3.ToString());

	std::println("Vector 1: {0}; Vector 1 length: {1}", v1.ToString(), v1.Length());

	v3 = v1.Normalize();
	std::println("Vector 1: {0}; Vector 1 normalized: {1}", v1.ToString(), v3.ToString());
}

int main()
{
	std::println("Game Maths with OpenGL and C++ 23!!\n");

	glfwSetErrorCallback(GLFWErrorCallback);

	if (!glfwInit())
	{
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "Game Programming!", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::println("ERROR: GLAD could not be initialized.");
		return -1;
	}

	// setting viewport to be the same as screen (possible to make smaller viewport and render things outside the main viewport)
	glViewport(0, 0, ScreenWidth, ScreenHeight);

	/*
		Creating shader object to compile our vertex shader
	*/
	// create object
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	/*
		param 1: shader object
		param 2: how many strings are being passed as src code
		param 3: source code
		param 4: ?
	*/
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	// checking if compilation was successful
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::println("ERROR: SHADER VERTEX COMPILATION FAILED. MORE INFO:\n{0}", infoLog);
	}

	// creating fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::println("ERROR: FRAGMENT SHADER COMPILATION FAILED. MORE INFO:\n{0}", infoLog);
	}

	// creating shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// linking vertex and fragment shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for erros on the linking process
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::println("ERROR: SHADER PROGRAM LINKING FAILED. MORE INFO:\n{0}", infoLog);
	}

	// after linking the shader into the program successfully, we can delete the shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// VERTEX INPUT
	/*
		Note: to render in 2D, just ignore the Z coords (set to 0)
	*/
	// vertex data of 2D triangle (position of 3 vertices)
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left
		 0.5f, -0.5f, 0.0f, // right
		 0.0f,  0.5f, 0.0f  // top
	};

	/*
		Allocating vertices on a buffer so we can go to the first step of
		graphics pipeline
	*/
	// create OpenGL buffer object and vertex array object
	unsigned int VBO;
	unsigned int VAO;

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	// first bind vertex array, then bind and set vertex buffer, and then configure vertex attributes
	glBindVertexArray(VAO);

	// binds created object to a target
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// copy user defined data to the currently bound buffer with target GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// telling opengl how to interpret the vertex attributes on the vertex data
	/*
		param 1: which vertex attr we want to configure
		param 2: size of the vertex attrb
		param 3: type of data
		param 4: whether data needs to be normalized
		param 5: stride - space between consecutive vertex attr (as each value in this case is a float 3d vector)
		param 6: offset where position data begins in the buffer
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// vertex attributes are off by default, we need to enable them
	glEnableVertexAttribArray(0);

	// after defining the attribute pointers, the vbo is registred as being bound to this vao, so we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// application main loop
	while (!glfwWindowShouldClose(window))
	{
		// input related functions go here (use native handling)
		HandleInput();

		// Clear screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render stuff
		// use the created program and the vertex array
		glUseProgram(shaderProgram);

		// bind vertex array of object you want to render
		glBindVertexArray(VAO);

		// then draw
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// unbind vertex array of rendered object
		glBindVertexArray(0);

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}