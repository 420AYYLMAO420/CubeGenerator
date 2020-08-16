#pragma once

#include <memory>

class Graphics {
public:
	Graphics(unsigned int winWidth, unsigned int winHeight);
	~Graphics();

	//clear back buffer and draw
	void Render(unsigned int key);
	class Camera* GetCamera() const { return CameraObj.get(); }//return pointer to camera
	//current number of cubes to be rendered
	int NumCubes;

private:

	unsigned int idProgram; //id of OpenGL program
	unsigned int WindowWidth, WindowHeight;//dimensions of window

	//components of Graphics
	std::unique_ptr<class VertexArray> VAO;
	std::unique_ptr<class VertexBuffer> VBuffer;
	std::unique_ptr<class IndexBuffer> IBuffer;
	std::unique_ptr<class VertexShader> VShader;
	std::unique_ptr<class FragmentShader> FShader;
	std::unique_ptr<class VertexLayout> InputLayout;
	std::unique_ptr<class Texture> TextureObj;
	std::unique_ptr<class Camera> CameraObj;
	std::shared_ptr<class Time> Timer;

};