#include "Shader.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<filesystem>

using namespace std;

std::string loadFromFile(std::string_view shader)
{
    auto p = std::filesystem::current_path();
    fstream shade;
    std::string code;
    shade.exceptions(std::fstream::failbit | std::fstream::badbit);
    try {
        shade.open(p.string() + shader.data());
        std::stringstream hold;
        hold << shade.rdbuf();
        code = hold.str();
        shade.close();
    }
    catch (exception& e)
    {
        Log("Failed to load file");
    }
    return code;
    
}
Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath, std::string_view geometryPath, std::string_view tcsPath, std::string_view tesPath)
{
    GLuint vshader{}, fshader{}, gshader{}, tesShader{}, tcsShader{};
    std::string vertex = loadFromFile(vertexPath);
    std::string fragment = loadFromFile(fragmentPath);

    this->shad = glCreateProgram();
    AddOptionalShaderStage(gshader, geometryPath, GL_GEOMETRY_SHADER);
    AddOptionalShaderStage(gshader, tcsPath, GL_TESS_CONTROL_SHADER);
    AddOptionalShaderStage(gshader, tesPath, GL_TESS_EVALUATION_SHADER);
    
    const char* vertexcode = vertex.c_str();
    const char* fragmentcode = fragment.c_str();

	vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vertexcode, NULL);
    glCompileShader(vshader);
    checkCompileErrors(vshader, "VERTEX");

    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fragmentcode, NULL);
    glCompileShader(fshader);
    checkCompileErrors(fshader, "FRAGMENT");

    glAttachShader(this->shad, vshader);
    glAttachShader(this->shad, fshader);
    glLinkProgram(this -> shad);

    checkCompileErrors(this->shad, "PROGRAM");
    if (geometryPath != "") glDeleteShader(gshader);
    if (tcsPath != "") glDeleteShader(tcsShader);
    if (tesPath != "") glDeleteShader(tesShader);
    glDeleteShader(vshader);
    glDeleteShader(fshader);
}


Shader::Shader(std::string_view computePath)
{
    GLuint CShader{};
    std::string compute = loadFromFile(computePath);
    const char* computeCode = compute.c_str();
    
    this->shad = glCreateProgram();

    CShader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(CShader, 1, &computeCode, NULL);
    glCompileShader(CShader);
    checkCompileErrors(CShader, "COMPUTE");

    glAttachShader(this->shad, CShader);
    glLinkProgram(this->shad);
    checkCompileErrors(this->shad, "PROGRAM");

    glDeleteShader(CShader);
}

void Shader::AddOptionalShaderStage(GLuint& shaderRef, std::string_view path, GLenum shaderType)
{
    if (path != "")
    {
        auto shaderName = CheckShaderType(shaderType);
        std::string shader = loadFromFile(path);
        const char* shaderCode = shader.c_str();
        shaderRef = glCreateShader(shaderType);
        glShaderSource(shaderRef, 1, &shaderCode, NULL);
        glCompileShader(shaderRef);
        checkCompileErrors(shaderRef, shaderName);
        glAttachShader(this->shad, shaderRef);
    }
}


std::string Shader::CheckShaderType(GLenum shaderType)
{
    if (shaderType == GL_GEOMETRY_SHADER)
        return "GEOMETRY";
    else if (shaderType == GL_TESS_CONTROL_SHADER)
        return "TESS CONTROL SHADER";
    else if (shaderType == GL_TESS_EVALUATION_SHADER)
        return "TESS EVALUATION SHADER";

    Log("Invalid ShaderType specified");
}
void Shader::checkCompileErrors(GLuint object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}

void Shader::SetFloat(string name, float value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->shad, name.c_str()), value);
}
void Shader::SetInteger(string name, int value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->shad, name.c_str()), value);
}
void Shader::SetVector2f(string name, float x, float y, bool useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->shad, name.c_str()), x, y);
}
void Shader::SetVector2f(string name, const glm::vec2& value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->shad, name.c_str()), value.x, value.y);
}
void Shader::SetVector3f(string name, float x, float y, float z, bool useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->shad, name.c_str()), x, y, z);
}
void Shader::SetVector3f(string name, const glm::vec3& value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->shad, name.c_str()), value.x, value.y, value.z);
}
void Shader::SetVector4f(string name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->shad, name.c_str()), x, y, z, w);
}
void Shader::SetVector4f(string name, const glm::vec4& value, bool useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->shad, name.c_str()), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(string name, const glm::mat4& matrix, bool useShader)
{
    if (useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->shad, name.c_str()), 1, false, glm::value_ptr(matrix));
}

void Shader::SetMatrix3(string name, const glm::mat3& matrix, bool useShader)
{
    if (useShader)
        this->use();
    glUniformMatrix3fv(glGetUniformLocation(this->shad, name.c_str()), 1, false, glm::value_ptr(matrix));
}

void Shader::use()
{
    glUseProgram(this->shad);
}

Shader::~Shader()
{
    glDeleteProgram(this->shad);
}
