#ifndef NOISE_H
#define NOISE_H
struct NoiseParams
{
    NoiseParams(int octaves, float scale, float persistence, float lacunarity) :
        octaves{ octaves }, scale{ scale }, persistence{ persistence }, lacunarity{ lacunarity }
    {
    }
    NoiseParams() {};
    int    octaves = 3;
    int    seed = 2;
    float  scale = 19.1f;
    float  persistence = 2.9f;
    float  lacunarity = 0.45f;
    glm::vec2 _offset = glm::vec2(50.0f, 27.0f);

    friend bool operator==(NoiseParams& noise1, NoiseParams& noise2)
    {
        return noise1.octaves == noise2.octaves && noise1.scale == noise2.scale && noise1.persistence == noise2.persistence &&
            noise1.lacunarity == noise2.lacunarity && noise1._offset == noise2._offset;
    }

    friend bool operator!=(NoiseParams& noise1, NoiseParams& noise2) { return !(noise1 == noise2); }
};
#endif