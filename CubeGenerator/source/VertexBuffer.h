#pragma once

#include "Buffer.h"

class VertexBuffer : public Buffer {
public:
	VertexBuffer(const void* vertices, size_t vertexamount);
	~VertexBuffer();

	void Bind() override;
	void Unbind() override;
};