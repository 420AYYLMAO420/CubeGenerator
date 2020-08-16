#pragma once

#include <memory>

class Window {

public:
	Window(const char* title, unsigned int width, unsigned int height);
	~Window();

	unsigned int HandleEvents();//handle keyboard events
	void ProcessImGui(int* InputInt);//handle ImGui processing
	int IsNotClosed();//if user closed the window, return false
	void SwapBuffers();


private:
	//pointer to the window
	struct GLFWwindow* pWindow;
	//title of window
	const char* Title;
	//dimensions of window
	unsigned int Width, Height;


};