#include "Shader.h"
#include <fstream>
#include <string>
#include "Log.h"
#include <GL/glew.h>

void Shader::ExtractAndCompile(SHADERTYPE type)
{
	//variable that holds the type of shader that called this function
	const char* shadertype = type == SHADERTYPE::VERTEX ? "Vertex" : "Fragment";
	//retrive string from shader source code
	std::ifstream FileStream(FilePath);
	std::string ShaderString = std::string(std::istreambuf_iterator<char>(FileStream), std::istreambuf_iterator<char>());
	const GLchar* ShaderCode = ShaderString.c_str();
	//supply shader source code to shader and compile it
	GL_USER_ERROR(glShaderSource(idShader, 1, &ShaderCode, NULL));
	GL_USER_ERROR(glCompileShader(idShader));
	//check if compilation succeeded or not
	GLint isCompiled;
	GL_USER_ERROR(glGetShaderiv(idShader, GL_COMPILE_STATUS, &isCompiled));
	char msgbuffer[2][50];
	sprintf_s(msgbuffer[0], "%s shader compiled", shadertype);
	sprintf_s(msgbuffer[1], "%s shader failed to compile", shadertype);
	PRINT_IF_ELSE(isCompiled, msgbuffer[0], msgbuffer[1]);
	
}

Shader::Shader()
	:idShader(NULL), idProgram(NULL), FilePath(nullptr)
{
}

//these functions will be defined in its derived classes
Shader::~Shader(){}
void Shader::Bind(){}
void Shader::Unbind(){}
