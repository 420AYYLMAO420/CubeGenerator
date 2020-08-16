#include "VertexBuffer.h"
#include "Log.h"
#include <GL/glew.h>


VertexBuffer::VertexBuffer(const void* vertices, size_t vertexamount)
{
	pData = vertices;
	dataAmount = vertexamount;

	//create vertex buffer and supply data
	GL_USER_ERROR(glGenBuffers(1, &idBuffer))
	PRINT_IF_ELSE(idBuffer > 0, "Created vertex buffer", "Failed to create vertex buffer");
	Bind();//must bind before supplying data
	GL_USER_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(pData) * dataAmount, pData, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	//clean up buffer
	GL_USER_ERROR(glDeleteBuffers(1, &idBuffer));
}

void VertexBuffer::Bind()
{
	GL_USER_ERROR(glBindBuffer(GL_ARRAY_BUFFER, idBuffer));
}

void VertexBuffer::Unbind()
{
	GL_USER_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
