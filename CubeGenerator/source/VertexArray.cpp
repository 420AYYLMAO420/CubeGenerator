#include "VertexArray.h"
#include "Log.h"
#include <GL/glew.h>

VertexArray::VertexArray()
{
	//create the vertex array id
	GL_USER_ERROR(glGenVertexArrays(1, &idVertexArray));
	PRINT_IF_ELSE(idVertexArray > 0, "Created vertex array", "Failed to create vertex array");
}

VertexArray::~VertexArray()
{
	//clean up vertex array
	GL_USER_ERROR(glDeleteVertexArrays(1, &idVertexArray));
}

void VertexArray::Bind()
{
	GL_USER_ERROR(glBindVertexArray(idVertexArray));
}

void VertexArray::Unbind()
{
	GL_USER_ERROR(glBindVertexArray(0));
}
