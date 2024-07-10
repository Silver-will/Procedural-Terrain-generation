#ifndef GENERAL_UTILITY_H
#define GENERAL_UTILITY_H
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<string>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<source_location>
using string = std::string;
using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat4 = glm::mat4;
void Log(const string message, const std::source_location loc = std::source_location::current());
enum class active_shading_model { none = 0, blinnPhong, PBR };
namespace Glob{
	extern GLfloat sensitivity;
	extern GLfloat lastX, lastY, xOffset, yOffset;
	extern bool fMouse;
	extern active_shading_model active;
	extern GLuint lightFBO, lightFBOTex;
}



#endif