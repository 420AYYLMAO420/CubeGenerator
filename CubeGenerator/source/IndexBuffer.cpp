#include "IndexBuffer.h"
#include "Log.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer(const void* indices, size_t indexamount)
{
	pData = indices;
	dataAmount = indexamount;

	//create index buffer and supply data
	GL_USER_ERROR(glGenBuffers(1, &idBuffer));
	PRINT_IF_ELSE(idBuffer > 0, "Created index buffer", "Failed to create index buffer");
	Bind();//must bind before supplying data
	GL_USER_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pData) * dataAmount, pData, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	//clean up buffer
	GL_USER_ERROR(glDeleteBuffers(1, &idBuffer));
}

void IndexBuffer::Bind()
{
	GL_USER_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idBuffer));
}

void IndexBuffer::Unbind()
{
	GL_USER_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
