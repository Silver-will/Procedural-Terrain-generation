#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out VS_OUT
{
float height;
vec2 TexCoord;
vec3 fragPos;
vec4 fragPosLightSpace;
}vs_out;

layout(std140, binding = 0) uniform Matrices
{
    uniform mat4 model;
    uniform mat4 mvp;
    uniform mat4 lightMatrix;
    float scale;
}

uniform Sampler2D noise;

void main()
{
    vs_out.fragPos = vec3(model * vec4(aPos,1.0f));
    vs_out.TexCoord = aTexCoord;
    
    //Check this
    float height = texture(noise, aTexCoord).r;

    float scaledHeight = scale * height;

    vec4 p = (aPos.x, scaledHeight,)
}