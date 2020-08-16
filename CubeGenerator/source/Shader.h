#pragma once

#include "Resource.h"

//enum used to specify the type of shader
enum class SHADERTYPE {
	VERTEX, FRAGMENT
};

class Shader : public Resource {
public:
	Shader();
	~Shader();

	virtual void Bind();
	virtual void Unbind();
	
	

protected:
	//extract the string from the shader file and compile the shader
	void ExtractAndCompile(SHADERTYPE type);

	//id of shader
	unsigned int idShader;
	//id of program
	unsigned int idProgram;
	//path of shader file
	const char* FilePath;

};


