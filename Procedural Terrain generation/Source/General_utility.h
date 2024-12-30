#ifndef GENERAL_UTILITY_H
#define GENERAL_UTILITY_H
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include<source_location>
#include<glm/gtc/type_ptr.hpp>

void Log(const std::string message, const std::source_location loc = std::source_location::current());
//Must pass a size argument if no data is passed
void CreateSSBO(GLuint& ssbo, GLuint binding, GLenum usage, GLuint size = 0, void* data = nullptr);
void UpdateSSBO(GLuint& ssbo, GLuint offset, GLuint size, void* data);
void CreateUniformBuffer(GLuint& id, GLuint size);
template<typename t>
void UploadToUniformBuffer(GLuint& id, GLuint bufferOffset, t& data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, id);
	glBufferSubData(GL_UNIFORM_BUFFER, bufferOffset, sizeof(data), glm::value_ptr(data));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
void CreateDepthBuffer(GLuint& depthMap, int width, int height);
#endif