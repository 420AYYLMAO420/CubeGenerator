#include "FragmentShader.h"
#include "Log.h"
#include <GL/glew.h>

FragmentShader::FragmentShader(const char* filepath, unsigned int& programID)
{
	FilePath = filepath;
	idProgram = programID;

	//create id and begin to create the rest of the shader
	GL_USER_ERROR(idShader = glCreateShader(GL_FRAGMENT_SHADER));
	PRINT_IF_ELSE(idShader > 0, "Fragment shader created", "Fragment shader creation failed");
	ExtractAndCompile(SHADERTYPE::FRAGMENT);
}

FragmentShader::~FragmentShader()
{
	//clean up shader
	GL_USER_ERROR(glDetachShader(idProgram, idShader));
	GL_USER_ERROR(glDeleteShader(idShader));
}

void FragmentShader::Bind()
{
	GL_USER_ERROR(glAttachShader(idProgram, idShader));
}

void FragmentShader::Unbind()
{
	GL_USER_ERROR(glDetachShader(idProgram, idShader));
}


