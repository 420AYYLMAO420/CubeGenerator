#version 430 core

//output color
out vec4 OutColor;

//input texture coordinates
in vec2 TextureST;

//texture that will be sampled
uniform sampler2D Texture;

void main()
{
	//interpolate between textures evenly
	OutColor = texture(Texture, TextureST);
}