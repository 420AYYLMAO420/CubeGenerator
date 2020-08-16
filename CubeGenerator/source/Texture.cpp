#include "Texture.h"
#include "Log.h"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION //must define implementation before including stb_image.h
#include <stb/stb_image.h>

Texture::Texture(unsigned int& program)
	:Width(0), Height(0), imgBuffer(nullptr), BitDepth(NULL), idProgram(program)
{}

Texture::~Texture()
{
	//free buffer and delete OpenGL textures
	stbi_image_free(imgBuffer);
	for (TextureUnit texture : Textures) {
		GL_USER_ERROR(glDeleteTextures(1, &texture.ID));
	}
}

//no need to call these functions
//glEnable(GL_TEXTURE_2D) only applies to the fixed function pipeline
//glDisable(GL_TEXTURE_2D) only applies to the fixed function pipeline
//the fragment shader is in use so an exception occurs if glEnable/glDisable is called
void Texture::Bind(){}
void Texture::Unbind(){}

void Texture::CreateTextures()
{
	//variable used to track the current texture to activate
	unsigned int TextureActivationFlag = GL_TEXTURE0;
	for (int i = 0; i < Textures.size(); i++) {
		//create id and activate texture
		glGenTextures(1, &Textures[i].ID);
		glActiveTexture(TextureActivationFlag + i);
		//bind texture to apply parameters to it
		glBindTexture(GL_TEXTURE_2D, Textures[i].ID); 
		//clamp the texture to the edges
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//bilinear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//OpenGL texture coordinate system has the bottom left corner as the origin
		//most image formats are drawn from top to bottom
		//the image must be flipped to match the origin of the image to origin of texture
		stbi_set_flip_vertically_on_load(true);
		//load image from file and store into buffer
		imgBuffer = stbi_load(Textures[i].FilePath, &Width, &Height, &BitDepth, 4);
		//define each texture 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgBuffer);
		//set the value of texture uniform found in shader to current index
		glUniform1i(glGetUniformLocation(idProgram, Textures[i].UniformName), i);
	}
}

	
