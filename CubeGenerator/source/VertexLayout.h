#pragma once

#include "Resource.h"
#include <vector>



class VertexLayout : public Resource {
public:
	VertexLayout(unsigned int program);
	~VertexLayout();

	void Bind();
	void Unbind();
	//register vertex attributes in OpenGL after initializing Attributes vector
	void CreateAttributes();

private:
	//struct used to define the contents of each vertex attribute
	struct Attribute {
		Attribute(const char* attribname, unsigned int numcomponents, size_t bufferoffset)
			:name(attribname), components(numcomponents), byteoffset(bufferoffset) {}
		const char* name; //name of attribute in shader
		unsigned int components; //how many components each attribute will have
		size_t byteoffset; //the offset in bytes from the start of each vertex to the start of this attribute
	};

public:
	//vector that stores all objects of type Attribute
	std::vector<Attribute> Attributes;
};