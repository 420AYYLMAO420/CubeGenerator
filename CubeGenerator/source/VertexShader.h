#pragma once

#include "Shader.h"

class VertexShader : public Shader {
public:
	VertexShader(const char* filepath, unsigned int& programID);
	~VertexShader();

	void Bind() override;
	void Unbind() override;
};