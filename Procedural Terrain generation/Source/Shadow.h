#ifndef SHADOW_H
#define	SHADOW_H
#include<vector>
#include"Shader.h"
#include<glm/glm.hpp>

void drawCascadeVolumeVisualizers(const std::vector<glm::mat4>& lightMatrices, Shader* shader);
void generateLightFBOAndTex(GLuint& lightFBO, GLuint& lightFBOTex);
std::vector<glm::mat4> getLightSpaceMatrices();
glm::mat4 getLightSpaceMatrix(const GLfloat nearPlane, const GLfloat farPlane);
std::vector<glm::vec4> getFrustrumCornersWorldSpace(const glm::mat4& projView);

namespace Shadow_values {
	extern std::vector<GLfloat> shadowCascadeLevels;
	extern bool shadow;
}
#endif // !SHADOW_H

