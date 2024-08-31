#include"General_utility.h"
#include<iostream>

void Log(const std::string message, const std::source_location loc)
{
	std::cout << "ERROR\n" << message << "\nin: "
		<< loc.file_name() << "\nAt or before line: " << loc.line() << "\n";
}

void CreateUniformBuffer(GLuint& id, GLuint size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_UNIFORM_BUFFER, id);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, id, 0, size);
}

void CreateSSBO(GLuint& ssbo,GLuint binding, GLenum usage, GLuint size , void* data )
{
	size = size == 0 ? sizeof(data) : size;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, usage);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void UpdateSSBO(GLuint& ssbo, GLuint offset, GLuint size, void* data)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER,offset,size,data);
}