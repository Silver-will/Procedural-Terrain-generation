#ifndef GENERAL_UTILITY_H
#define GENERAL_UTILITY_H
#include<GLAD/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include<source_location>
void Log(const std::string message, const std::source_location loc = std::source_location::current());
#endif