#pragma once

#include "Resource.h"

class Buffer : public Resource {
public:

	Buffer() : idBuffer(0), pData(nullptr), dataAmount(0) {}
	~Buffer() {}
	
	virtual void Bind() {}
	virtual void Unbind() {}
protected:

	unsigned int idBuffer;// id of buffer
	const void* pData;//data that the buffer will use
	size_t dataAmount;//how many units(vertices/indices) the buffer will use
};