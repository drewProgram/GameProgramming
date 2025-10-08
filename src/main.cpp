#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <print>

#include "Vector.h"
#include "Shader.h"

const unsigned int ScreenWidth = 640;
const unsigned int ScreenHeight = 480;

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

	// creating shader program
	Shader triangleShader("src/shaders/crazyTriangle.vert", "src/shaders/crazyTriangle.frag");

	// VERTEX INPUT
	/*
		Note: to render in 2D, just ignore the Z coords (set to 0)
	*/
	// vertex data of 2D triangle (position of 3 vertices)
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
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
		param 6: offset where this attr data begins in the buffer
	*/
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// vertex attributes are off by default, we need to enable them
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// after defining the attribute pointers, the vbo is registred as being bound to this vao, so we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
		triangleShader.Use();

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