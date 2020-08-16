#pragma once

#include "Shader.h"

class FragmentShader : public Shader {
public:
	FragmentShader(const char* filepath, unsigned int& programID);
	~FragmentShader();

	void Bind() override;
	void Unbind() override;
};