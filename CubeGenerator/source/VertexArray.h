#pragma once

#include "Resource.h"

class VertexArray : public Resource {
public:

	VertexArray();
	~VertexArray();

	void Bind();
	void Unbind();
private:
	//id of vertex array object
	unsigned int idVertexArray;
};