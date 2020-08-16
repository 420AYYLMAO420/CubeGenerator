#include "VertexShader.h"
#include "Log.h"
#include <string>
#include <fstream>
#include <GL/glew.h>

VertexShader::VertexShader(const char* filepath, unsigned int& programID)
{
	FilePath = filepath;
	idProgram = programID;

	//create shader and compile its code
	GL_USER_ERROR(idShader = glCreateShader(GL_VERTEX_SHADER));
	PRINT_IF_ELSE(idShader > 0, "Vertex shader created", "Vertex shader creation failed");
	ExtractAndCompile(SHADERTYPE::VERTEX);
}

VertexShader::~VertexShader()
{
	//clean up shader
	GL_USER_ERROR(glDetachShader(idProgram, idShader));
	GL_USER_ERROR(glDeleteShader(idShader));
}

void VertexShader::Bind()
{
	GL_USER_ERROR(glAttachShader(idProgram, idShader));
}

void VertexShader::Unbind()
{
	GL_USER_ERROR(glAttachShader(idProgram, idShader));
}
