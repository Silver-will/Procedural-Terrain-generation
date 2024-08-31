#ifndef BUFFERD_H
#define BUFFERD_H
#include "General_utility.h"
#include "Math.h"

struct UniformData {
	glm::mat4 proj;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 mvp;
	glm::mat4 lightMatrix;
};

#endif