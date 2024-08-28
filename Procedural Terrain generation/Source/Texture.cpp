#include "Texture.h"
#include "General_utility.h"
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include<filesystem>

GLuint Texture::Totalindex = 0;

Texture::Texture(std::string texturePath, GLenum wrapping, GLenum sampleFilter):index{ Totalindex }
{
	auto p = std::filesystem::current_path();
	texturePath = p.string() + texturePath;

	GLint width, height, nrchannels;
	glGenTextures(1, &this->TexID);
	
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrchannels, 0);

	this->width = width;
	this->height = height;

	if (data)
	{
		GLenum Imgformat = GL_RGBA;
		GLenum internalFormat = GL_SRGB_ALPHA;
		if (nrchannels == 1)
			internalFormat = Imgformat = GL_RED;
		else if (nrchannels == 2)
			internalFormat = Imgformat = GL_RG;
		else if (nrchannels == 3)
		{
			internalFormat = GL_SRGB;
			Imgformat = GL_RGB;
		}
		this->format = Imgformat;

		glBindTexture(this->TexID, GL_TEXTURE_2D);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, Imgformat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sampleFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sampleFilter);
	}
	else
	{
		Log("Failed to load texture data");
	}
	stbi_image_free(data);
	glBindTexture(0, GL_TEXTURE_2D);
	Totalindex++;
}

Texture::Texture(int width, int height, void* data, GLenum format, GLenum wrapping, GLenum sampleFilter):index{ Totalindex }
{
	this->width = width;
	this->height = height;
	this->format = format;

	glGenTextures(1, &this->TexID);
	glBindTexture(this->TexID, GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sampleFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sampleFilter);

	Totalindex++;
}

void Texture::CreateTexture(int width, int height, void* data, GLenum format, GLenum wrapping, GLenum sampleFilter)
{
	this->width = width;
	this->height = height;
	this->format = format;

	glGenTextures(1, &this->TexID);
	glBindTexture(this->TexID, GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sampleFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sampleFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(0, GL_TEXTURE_2D);
}
void Texture::UpdateTexture(void* data)
{
	//glBindTexture(this->TexID, GL_TEXTURE_2D);
	glTextureSubImage2D(this->TexID, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
	//glBindTexture(0, GL_TEXTURE_2D);
}


void Texture::BindTexture()
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, TexID);
}