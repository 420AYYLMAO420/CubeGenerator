#pragma once

#include "Buffer.h"

class IndexBuffer : public Buffer {
public:
	IndexBuffer(const void* indices, size_t indexamount);
	~IndexBuffer();

	void Bind() override;
	void Unbind() override;

};