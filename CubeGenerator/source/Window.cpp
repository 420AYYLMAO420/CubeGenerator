#include "Window.h"
#include <GLFW/glfw3.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Log.h"

Window::Window(const char* title, unsigned int width, unsigned int height)
	:Title(title), Width(width), Height(height)
{

	PRINT_IF_ELSE(glfwInit() == GLFW_TRUE, "Initialized GLFW", "Failed to initialize GLFW");
	//suggest to window that the app wants OpenGL 4.3 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create the window and OpenGL context
	pWindow = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);
	glfwMakeContextCurrent(pWindow);
	

	PRINT_IF_ELSE(ImGui::CreateContext(), "Created ImGui context", "Failed to create ImGui context");
	PRINT_IF_ELSE(ImGui_ImplGlfw_InitForOpenGL(pWindow, false), "Intialized ImGui for GLFW", "Failed to initialize ImGui for GLFW");
	PRINT_IF_ELSE(ImGui_ImplOpenGL3_Init(), "Intialized ImGui for OpenGL", "Failed to initialize ImGui for OpenGL");
	ImGui::StyleColorsDark();
}

Window::~Window()
{
	//clean up window
	glfwDestroyWindow(pWindow);
	glfwTerminate();
	ImGui_ImplGlfw_Shutdown();
}

unsigned int Window::HandleEvents()
{
	
	glfwPollEvents();

	if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
		return GLFW_KEY_W;
	if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
		return GLFW_KEY_S;
	if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
		return GLFW_KEY_A;
	if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
		return GLFW_KEY_D;
	if (glfwGetKey(pWindow, GLFW_KEY_Q) == GLFW_PRESS)
		return GLFW_KEY_Q;
	if (glfwGetKey(pWindow, GLFW_KEY_E) == GLFW_PRESS)
		return GLFW_KEY_E;


	return 0;
}

void Window::ProcessImGui(int* InputInt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Cube Generator");
	ImGui::InputInt("How many cubes?", InputInt);
	if (*InputInt < 0) *InputInt = 0;
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int Window::IsNotClosed()
{
	return !glfwWindowShouldClose(pWindow);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(pWindow);
}

