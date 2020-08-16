#version 430 core

//take in attributes of vertex
layout(location = 0) in vec3 Position2D;
layout(location = 1) in vec2 TextureUV;

//output texture coordinates
out vec2 TextureST;

//matrices to be multiplied 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	//leave attributes unmodified
	gl_Position = projection * view * model * vec4(Position2D, 1.0);
	TextureST = vec2(TextureUV.x, TextureUV.y);
}