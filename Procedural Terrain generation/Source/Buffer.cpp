#ifndef BUFFER_H
#define BUFFER_H
#include "Buffer.h"

void CreateUniformBuffer(GLuint& id, GLuint size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_UNIFORM_BUFFER, id);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, id, 0, size);
}

/*template<typename t>
void UploadToUniformBuffer(GLuint& id, GLuint bufferOffset, t& data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, id);
	glBufferSubData(GL_UNIFORM_BUFFER, bufferOffset, sizeof(data), glm::value_ptr(data));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
*/
#endif