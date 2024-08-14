#ifndef MATH_H
#define MATH_H
#include<random>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

float Inv_Lerp(float a, float b, float v) { return (v - a) / (b - a); }
inline glm::vec3 lerp(const glm::vec3& u, const glm::vec3& v, const float x) { return u + x * (v - u); }
inline glm::vec3 clamp(const glm::vec3& v, const glm::vec3& c0, const glm::vec3& c1) { return min(max(v, c0), c1); }
inline float lerp(const float u, const float v, const float x) { return u + x * (v - u); }

#endif