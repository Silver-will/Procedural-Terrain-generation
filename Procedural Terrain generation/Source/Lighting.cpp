#include "Lighting.h"

Lighting::Lighting(const glm::vec3& dir, const glm::vec3& pos, 
	const glm::vec3& camPos, const glm::vec3& col) : lightDir{ dir }, lightPos{ pos }, cameraPos{camPos}
	, lightCol{ col } {}

void Lighting::UploadLightValues(Shader& shad)
{
	shad.SetVector3f("cameraPos", cameraPos, false);
	shad.SetVector3f("lightDirection", lightDir, false);
	shad.SetVector3f("lightColor", lightCol, false);
}