#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <print>
#include <cmath>
#include <memory>

#include "Vector.h"
#include "Shader.h"
#include "Entity.h"
#include "VectorShape.h"

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
	Shader vecShader("src/shaders/vectorShape.vert", "src/shaders/vectorShape.frag");

	unsigned int vecVBO;
	unsigned int vecVAO;

	glGenBuffers(1, &vecVBO);
	glGenVertexArrays(1, &vecVAO);

	// with shared ptr we can use polymorphism and use the same shape instance for all entities
	std::shared_ptr<VectorShape> vecShape = std::make_shared<VectorShape>(&vecShader, vecVAO, vecVBO);

	Entity vecTest(vecShape);
	vecTest.position = { 0.1f, 0.0f, 0.0f };
	vecTest.randomVec = { 0.2f, 0.3f, 0.0f };
	
	Entity vecTest2(vecShape);
	vecTest2.position = { 0.0f, 0.5f, 0.0f };
	vecTest2.randomVec = { -0.8f, 0.8f, 0.0f };
	vecTest2.color = { 0.0f, 1.0f, 0.0f };

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
		vecTest.Render();
		vecTest2.Render();

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vecVAO);
	glDeleteBuffers(1, &vecVBO);
	glDeleteProgram(vecShader.id);

	// Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}