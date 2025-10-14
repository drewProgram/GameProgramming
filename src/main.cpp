#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <windows.h>

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

const unsigned int ScreenWidth = 1280;
const unsigned int ScreenHeight = 800;

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

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	glfwSetErrorCallback(GLFWErrorCallback);

	if (!glfwInit())
	{
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const char* glsl_version = "#version 460";

	float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only

	GLFWwindow* window = glfwCreateWindow((int)(main_scale * ScreenWidth), (int)(main_scale * ScreenHeight), "Game Programming!", NULL, NULL);
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


	/* 
		ImGui setup 
	*/
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable gamepad controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable keyboard controls

	// setup style
	ImGui::StyleColorsDark();

	// setup scaling
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(main_scale);                // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
	style.FontScaleDpi = main_scale;                // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

	// setup platform/renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details. If you like the default font but want it to scale better, consider using the 'ProggyVector' from the same author!
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	// - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
	//style.FontSizeBase = 20.0f;
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf");
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf");
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf");
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf");
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf");
	//IM_ASSERT(font != nullptr);

	/* 
	/////////////////////// END ImGui SETUP ///////////////////////////////////////
	*/

	// ImGui states
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool vec1PropsVisible = true;

	// creating shader program
	Shader vecShader("src/shaders/vectorShape.vert", "src/shaders/vectorShape.frag");

	unsigned int vecVBO;
	unsigned int vecVAO;

	glGenBuffers(1, &vecVBO);
	glGenVertexArrays(1, &vecVAO);

	// with shared ptr we can use polymorphism and use the same shape instance for all entities
	std::shared_ptr<VectorShape> vecShape = std::make_shared<VectorShape>(&vecShader, vecVAO, vecVBO);

	Entity vecTest(vecShape);
	vecTest.position = { 0.0f, 0.0f, 0.0f };
	vecTest.randomVec = { 0.2f, -0.3f, 0.0f };
	vecTest.color = { 0.2f, 0.3f, 0.0f };
	ImVec4 color1 = ImVec4(vecTest.color.x, vecTest.color.y, vecTest.color.z, 1.00f);
	
	Entity vecTest2(vecShape);
	vecTest2.position = { 0.0f, 0.5f, 0.0f };
	vecTest2.randomVec = { -0.8f, -0.5f, 0.0f };
	vecTest2.color = { 0.0f, 1.0f, 0.0f };
	ImVec4 color2 = ImVec4(vecTest2.color.x, vecTest2.color.y, vecTest2.color.z, 1.00f);

	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// application main loop
	while (!glfwWindowShouldClose(window))
	{
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		// setting viewport to be the same as screen (possible to make smaller viewport and render things outside the main viewport)
		glViewport(0, 0, display_w, display_h);
		// Clear screen
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// input related functions go here (use native handling)
		HandleInput();

		if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
		{
			ImGui_ImplGlfw_Sleep(10);
			continue;
		}

		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Vector manipulation sliders
		{
			ImGui::Begin("Vector manipulation");
			ImGui::SetWindowSize(ImVec2(500, 250));

			if (ImGui::CollapsingHeader("Vector 1 properties", true))
			{
				ImGui::Text("Position");
				ImGui::SliderFloat("V1 P.X", &vecTest.position.x, -1.0f, 1.0f);
				ImGui::SliderFloat("V1 P.Y", &vecTest.position.y, -1.0f, 1.0f);

				ImGui::Text("Value");
				ImGui::SliderFloat("V1 V.X", &vecTest.randomVec.x, -1.0f, 1.0f);
				ImGui::SliderFloat("V1 V.Y", &vecTest.randomVec.y, -1.0f, 1.0f);

				ImGui::ColorEdit3("V1 Color", (float*)&color1);
				vecTest.color = { color1.x * color1.w, color1.y * color1.w, color1.z * color1.w };
			}

			if (ImGui::CollapsingHeader("Vector 2 properties", true))
			{
				ImGui::Text("Position");
				ImGui::SliderFloat("V2 P.X", &vecTest2.position.x, -1.0f, 1.0f);
				ImGui::SliderFloat("V2 P.Y", &vecTest2.position.y, -1.0f, 1.0f);

				ImGui::Text("Value");
				ImGui::SliderFloat("V2 V.X", &vecTest2.randomVec.x, -1.0f, 1.0f);
				ImGui::SliderFloat("V2 V.Y", &vecTest2.randomVec.y, -1.0f, 1.0f);

				ImGui::ColorEdit3("V2 Color", (float*)&color2);
				vecTest2.color = { color2.x * color2.w, color2.y * color2.w, color2.z * color2.w };
			}

			ImGui::ColorEdit3("Clear color", (float*)&clear_color);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

			ImGui::End();
		}

		// render stuff (always render opengl first)
		vecTest.Render();
		vecTest2.Render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// check and call events and swap buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &vecVAO);
	glDeleteBuffers(1, &vecVBO);
	glDeleteProgram(vecShader.id);

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}