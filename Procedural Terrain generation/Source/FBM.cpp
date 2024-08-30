#include "FBM.h"
#include "Math.h"
#include <numeric>
#include <random>
#include <GLFW/glfw3.h>

float FBM::Noise2(float x, float y)
{
    int X = (int)floor(x) & 0xff;
    int Y = (int)floor(y) & 0xff;
    x -= floorf(x);
    y -= floorf(y);
    float u = Fade(x);
    float v = Fade(y);
    int   A = (perm[X] + Y) & 0xff;
    int   B = (perm[X + 1] + Y) & 0xff;

    return lerp(lerp(Grad(perm[A], x, y), Grad(perm[B], x - 1, y), u),
        lerp(Grad(perm[A + 1], x, y - 1), Grad(perm[B + 1], x - 1, y - 1), u), v);
}

FBM::FBM(int width, int height): noiseWidth{width}, noiseHeight{height}
{ 
    noiseMapValues.resize(256 * 256);
    GenerateNoiseMap();
    CreateNoiseTexture();
}
float FBM::Fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }
float FBM::Grad(int hash, float x) { return (hash & 1) == 0 ? x : -x; }
float FBM::Grad(int hash, float x, float y) { return ((hash & 1) == 0 ? x : -x) + ((hash & 2) == 0 ? y : -y); }

void FBM::GenerateNoiseMap()
{
    if (noise1.scale <= 0.0f || noise2.scale <= 0.0f)
    {
        noise1.scale = 0.1f;
        noise2.scale = 0.1f;
    }
   
    float maxNoise = std::numeric_limits<float>::min();
    float minNoise = std::numeric_limits<float>::max();
    
    std::vector<glm::vec2> octaveOffsets(noise1.octaves);
    
    std::mt19937 gen(noise1.seed);
    std::uniform_real_distribution<> dis(-10000.0, 10000.0);


    for (int i = 0; i < noise1.octaves; i++)
    {
        octaveOffsets.at(i).r = dis(gen) + noise1._offset.r;
        octaveOffsets.at(i).g = dis(gen) + noise1._offset.g;
    }

    for (int y = 0; y < noiseHeight; y++)
    {
        for (int x = 0; x < noiseWidth; x++)
        {
            float noiseHeight = Pattern((float)x, (float)y,octaveOffsets);

            if (noiseHeight > maxNoise)
            {
                maxNoise = noiseHeight;
            }
            else if (noiseHeight < minNoise)
            {
                minNoise = noiseHeight;
            }
            noiseMapValues[x + y * noiseWidth] = noiseHeight;
        }
    }
    for (int y = 0; y < noiseHeight ; y++)
    {
        for (int x = 0; x < noiseWidth; x++)
        {
            noiseMapValues[x + y * noiseWidth] = Inv_Lerp(minNoise, maxNoise, noiseMapValues[x + y * noiseWidth]);
        }
    }

}

float FBM::Pattern(float x, float y,std::vector<glm::vec2>& octaveOffsets)
{
    glm::vec2 q = glm::vec2(Fbm(x, y, noise1.octaves, octaveOffsets, noise1.scale, noise1.persistence, noise1.lacunarity),
        Fbm(x + 5.2f, y + 1.3f, noise2.octaves, octaveOffsets, noise2.scale, noise2.persistence, noise2.lacunarity));

    int octaves = (noise1.octaves + noise2.octaves) / 2;
    float scale = (noise1.scale + noise2.scale) /2;
    float lacunarity = (noise1.lacunarity + noise2.lacunarity) / 2;
    float persistence = (noise1.persistence + noise2.persistence) / 2;
    return Fbm(x + q[0] * 4.0f, y + q[1] * 4.0f, octaves, octaveOffsets, scale, persistence, lacunarity);
}

float FBM::Fbm(float x, float y, int& octaves, std::vector<glm::vec2>& octaveOffsets, float& scale, float persistence, float lacunarity)
{
    float amplitude = 1.0f;
    float frequency = 1.0f;
    float noiseHeight = 0.0f;
    for (int i = 0; i < octaves; i++)
    {
        float sample_x = x / scale * frequency + octaveOffsets[i].r;
        float sample_y = y / scale * frequency + octaveOffsets[i].g;

        float perlinValue = Noise2(sample_x, sample_y) * 2 - 1;
        noiseHeight += perlinValue * amplitude;

        amplitude *= persistence;
        frequency *= lacunarity;
    }
    return noiseHeight;
}

void FBM::CreateNoiseTexture()
{
    noisetexture.CreateTexture(noiseWidth, noiseHeight, noiseMapValues.data(), GL_RED, GL_REPEAT, GL_LINEAR);
    //UpdateNoiseTexture();
}

void FBM::UpdateNoiseTexture()
{
    noisetexture.UpdateTexture(noiseMapValues.data(),GL_FLOAT);
}

bool FBM::ValueChanged()
{
    if (noise1 != noise1_prev || noise2 != noise2_prev)
    {
        noise1_prev = noise1;
        noise2_prev = noise2;
        return true;
    }
    return false;
}