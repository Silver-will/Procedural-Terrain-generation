#ifndef NOISE_H
#define NOISE_H
struct NoiseParams
{
    NoiseParams(int octaves, float scale, float persistence, float lacunarity) :
        _octaves{ octaves }, _scale{ scale }, _persistence{ persistence }, _lacunarity{ lacunarity }
    {
    }
    NoiseParams() {};
    int    _octaves = 3;
    int seed = 2;
    float  _scale = 19.1f;
    float  _persistence = 2.9f;
    float  _lacunarity = 0.45f;
    glm::vec2 _offset = glm::vec2(50.0f, 27.0f);

    friend bool operator==(NoiseParams& noise1, NoiseParams& noise2)
    {
        return noise1._octaves == noise2._octaves && noise1._scale == noise2._scale && noise1._persistence == noise2._persistence &&
            noise1._lacunarity == noise2._lacunarity && noise1._offset == noise2._offset;
    }

    friend bool operator!=(NoiseParams& noise1, NoiseParams& noise2) { return !(noise1 == noise2); }
};
#endif