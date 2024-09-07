#pragma once
#include "Math.h"
#include "Shader.h"
struct Lighting
{
	Lighting(const glm::vec3& dir = glm::vec3(-1.0,-1.0,0), const glm::vec3& pos = glm::vec3(0, 0, 0), const glm::vec3& camPos = glm::vec3(0, 0, 0), const glm::vec3& col = glm::vec3(1.0,1.0, 1.0));
	void UploadLightValues(Shader& shad);
	glm::vec3 lightDir;
	glm::vec3 lightPos;
	glm::vec3 cameraPos;
	glm::vec3 lightCol;
};

