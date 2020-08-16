#include "Graphics.h"
#include "Log.h"
#include "VertexArray.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexLayout.h"
#include "Texture.h"
#include "Time.h"
#include "Camera.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <random>

//defines the content of a single vertex
struct VERTEX {
	struct {
		float X, Y, Z;
	} Position;//position coordinates
	struct {
		float U, V;
	} Texture;//texture coordinates
};

//array of vertices the vertex buffer will use
VERTEX Vertices[] = {

	{-0.5f, -0.5f, 0.5f, 0.f, 0.f}, //0
	{-0.5f,  0.5f, 0.5f, 0.f, 1.f}, //1
	{ 0.5f,  0.5f, 0.5f, 1.f, 1.f}, //2
	{ 0.5f, -0.5f, 0.5f, 1.f, 0.f}, //3
	{-0.5f, -0.5f,-0.5f, 0.f, 0.f}, //4
	{-0.5f,  0.5f,-0.5f, 0.f, 1.f}, //5
	{ 0.5f,  0.5f,-0.5f, 1.f, 1.f}, //6
	{ 0.5f, -0.5f,-0.5f, 1.f, 0.f}, //7
	{-0.5f, -0.5f,-0.5f, 0.f, 1.f}, //8
	{ 0.5f, -0.5f,-0.5f, 1.f, 1.f}, //9
	{-0.5f,  0.5f, 0.5f, 0.f, 0.f}, //10
	{ 0.5f,  0.5f, 0.5f, 1.f, 0.f}, //11
	{-0.5f,  0.5f, 0.5f, 1.f, 1.f}, //12
	{ 0.5f, -0.5f, 0.5f, 0.f, 0.f}, //13
	{ 0.5f,  0.5f, 0.5f, 0.f, 1.f}, //14
	{-0.5f, -0.5f, 0.5f, 1.f, 0.f}, //15
};

//array of indices the index buffer will use
unsigned int Indices[] = {	 
	0, 1, 2, 2, 3, 0, //front
	4, 5, 6, 6, 7, 4, //back
	0, 8, 9, 9, 3, 0, //bottom
	10, 5, 6, 6, 11, 10, //top
	4, 5, 12, 12, 15, 4, //left
	13, 14, 6, 6, 7, 13 //right
};

std::vector<glm::vec3> CubePositions; //vector that will hold all positions of each cube

Graphics::Graphics(unsigned int winWidth, unsigned int winHeight)
	: WindowWidth(winWidth), WindowHeight(winHeight), NumCubes(0)
{

	//initialize GLEW
	PRINT_IF_ELSE(glewInit() != -1, "Initialized GLEW", "Failed to initialize GLEW");

	//create OpenGL program
	GL_USER_ERROR(idProgram = glCreateProgram());
	PRINT_IF_ELSE(idProgram, "Created OpenGL program", "Failed to create OpenGL program");

	//create vertex shader
	VShader = std::make_unique<VertexShader>("shaders/VertexShader.glsl", idProgram);
	VShader->Bind();

	//create fragment shader
	FShader = std::make_unique<FragmentShader>("shaders/FragmentShader.glsl", idProgram);
	FShader->Bind();

	//set OpenGL program for use
	GL_USER_ERROR(glLinkProgram(idProgram));
	glValidateProgram(idProgram);
	GLint isValid;
	glGetProgramiv(idProgram, GL_VALIDATE_STATUS, &isValid);
	PRINT_IF_ELSE(isValid, "Validated OpenGL program", "OpenGL program is not valid");
	GL_USER_ERROR(glUseProgram(idProgram));

	//create vertex array
	VAO = std::make_unique<VertexArray>();
	VAO->Bind();

	//create vertex buffer
	VBuffer = std::make_unique<VertexBuffer>(Vertices, sizeof(Vertices) / sizeof(float));
	VBuffer->Bind();

	//create index buffer
	IBuffer = std::make_unique<IndexBuffer>(Indices, std::size(Indices));
	IBuffer->Bind();

	//create input layout and register each vertex attribute
	InputLayout = std::make_unique<VertexLayout>(idProgram);
	InputLayout->Attributes.emplace_back("Position2D",
		sizeof(Vertices->Position)/sizeof(float), 0);
	InputLayout->Attributes.emplace_back("TextureUV", 
		sizeof(Vertices->Texture) / sizeof(float), sizeof(Vertices->Position));
	InputLayout->CreateAttributes();
	InputLayout->Bind();

	//create texture manager and create textures
	TextureObj = std::make_unique<Texture>(idProgram);
	TextureObj->Textures.emplace_back("resources/Captain Spongebob.png", "Texture");
	TextureObj->CreateTextures();

	//create and start timer 
	Timer = std::make_unique<Time>();
	Timer->Start();

	//seed using time
	srand(static_cast<unsigned int>(Timer->GetTimeSinceStart()));

	//create camera with its position 20.f away from world origin using Z-axis
	CameraObj = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 20.0f), 
		glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), .05f);

	//set background color to black
	glClearColor(0.f, 0.f, 0.f, 1.f);
	//enable depth testing to create cubes
	glEnable(GL_DEPTH_TEST);
}

Graphics::~Graphics()
{
	//clean up OpenGL
	GL_USER_ERROR(glDeleteProgram(idProgram));
}

void Graphics::Render(unsigned int key)
{
	//clear back buffer
	GL_USER_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	//set the camera base speed to 3.f using delta time to keep the speed consistent among each machine
	CameraObj->Speed = 3.f * Timer->GetDeltaTime();
	//move the camera in a direction based on the key pressed
	CameraObj->Move((CameraDirection)key);
	//device used to generate random numbers
	std::random_device RandDevice;
	//random number engine
	std::mt19937 RandEngine(RandDevice());
	//distribution of random floats uniformly
	std::uniform_real_distribution<float> RandDist(-5.f, 5.f);
	//static variable used to hold the previous value of NumCubes
	static int PrevNumCubes = 0;

	//if the user wants more cubes, create new cubes
	if (PrevNumCubes < NumCubes) {
		for (PrevNumCubes; PrevNumCubes < NumCubes; PrevNumCubes++)
			CubePositions.emplace_back(RandDist(RandEngine), RandDist(RandEngine), RandDist(RandEngine));
	}
	//if the user wants less cubes, remove cubes
	else if (PrevNumCubes > NumCubes) {
		for (PrevNumCubes; PrevNumCubes > NumCubes; PrevNumCubes--)
			CubePositions.pop_back();
	}

	//projection matrix
	glm::mat4 Projection;
	Projection = glm::perspective(glm::radians(45.0f), (float)(WindowWidth / WindowHeight), 0.1f, 100.0f);
	int ProjectionLocation = glGetUniformLocation(idProgram, "projection");
	glUniformMatrix4fv(ProjectionLocation, 1, GL_FALSE, glm::value_ptr(Projection));
	for (glm::vec3 Position : CubePositions) {
		//rotate and translate cubes
		glm::mat4 Model = glm::mat4(1.0f);
		Model = glm::translate(Model, Position);
		Model = glm::rotate(Model, Timer->GetTimeSinceStart(), glm::vec3(1.f, 1.f, 1.f));
		//send model and view matrices to shaders
		int ModelLocation = glGetUniformLocation(idProgram, "model");
		glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));
		int ViewLocation = glGetUniformLocation(idProgram, "view");
		glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(CameraObj->GetView()));
		//draw call
		GL_USER_ERROR(glDrawElements(GL_TRIANGLES, std::size(Indices), GL_UNSIGNED_INT, (void*)0));
	}
	
}