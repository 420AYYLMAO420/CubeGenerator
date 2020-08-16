#pragma once

#include <memory>

class App {

public:
	App(const char* title, unsigned int width, unsigned int height);
	~App();
	void Run(); //main loop

private:
	std::unique_ptr<class Window> window; //create an instance of a window
	std::unique_ptr<class Graphics> graphics; //create graphics that window will use
};