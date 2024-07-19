#ifndef SHADER_H
#define SHADER_H
#include"General_utility.h"
#include<filesystem>
#include<string_view>

std::string loadFromFile(std::string_view shader);
struct Shader {
	Shader(std::string_view vertexPath, std::string_view fragmentPath, std::string_view geometryPath = "", std::string_view tcsPath = "", std::string_view tesPath = "");
    Shader(std::string_view computePath);
    void    checkCompileErrors(GLuint object, std::string type);
	void    use();
    void    SetFloat(std::string name, float value, bool useShader = false);
    void    SetInteger(std::string name, int value, bool useShader = false);
    void    SetVector2f(std::string name, float x, float y, bool useShader = false);
    void    SetVector2f(std::string name, const glm::vec2& value, bool useShader = false);
    void    SetVector3f(std::string name, float x, float y, float z, bool useShader = false);
    void    SetVector3f(std::string name, const glm::vec3& value, bool useShader = false);
    void    SetVector4f(std::string name, float x, float y, float z, float w, bool useShader = false);
    void    SetVector4f(std::string name, const glm::vec4& value, bool useShader = false);
    void    SetMatrix4(std::string name, const glm::mat4& matrix, bool useShader = false);
    void    SetMatrix3(std::string name, const glm::mat3& matrix, bool useShader = false);
    void AddOptionalShaderStage(GLuint& shaderRef, std::string_view path, GLenum shaderType);
   std::string CheckShaderType(GLenum shaderType);

	GLuint shad;
	~Shader();
};
#endif