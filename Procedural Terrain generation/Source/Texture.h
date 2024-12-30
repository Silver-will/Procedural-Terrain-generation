#ifndef TEXTURE_H
#define TEXTURE_H

#include<GLFW/glfw3.h>
#include<string>
#include"General_utility.h"

struct Texture
{
	Texture() :index{ Totalindex } { Totalindex++; };
	//Load Texture from image file
	Texture(std::string texturePath, GLenum wrapping, GLenum sampleFilter);
	//Create empty texture in memory
	Texture(int width,int height,void* data, GLenum format, GLenum wrapping, GLenum sampleFilter);
	//Update texture data
	void CreateTexture(int width, int height, GLenum internalFormat, GLenum format, GLenum wrapping, GLenum sampleFilter,float* data = NULL);
	void UpdateTexture(void* data, GLenum dataFormat);
	void BindTexture();
	
	static GLuint Totalindex;
	GLuint index;
	GLuint TexID{};
	GLenum format{};
	int width{};
	int height{};
};
#endif