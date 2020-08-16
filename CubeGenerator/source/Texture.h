#pragma once

#include "Resource.h"
#include <vector>

class Texture : public Resource {
public:

	Texture(unsigned int& program);
	~Texture();

	void Bind();
	void Unbind();
	//create and activate OpenGL textures after initializing Textures vector
	void CreateTextures();

private:
	//struct used to define the contents of each texture
	struct TextureUnit {
		TextureUnit(const char* path, const char* name) 
			:FilePath(path), UniformName(name), ID(NULL)
		{}
		const char* FilePath;
		const char* UniformName;
		unsigned int ID;
	};

public: 
	//vector used to store all objects of type TextureUnit
	std::vector<TextureUnit> Textures;

private:
	//id of program
	unsigned int idProgram;
	//buffer used to store the contents of the image
	unsigned char* imgBuffer;
	//dimensions of image
	int Width, Height;
	//bits-per-pixel of image
	int BitDepth;
	
};