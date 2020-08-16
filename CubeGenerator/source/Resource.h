#pragma once

class Resource {
public:

	//each resource must have a way of binding/unbinding to the pipeline
	virtual void Bind() = 0;
	virtual void Unbind() = 0;
};