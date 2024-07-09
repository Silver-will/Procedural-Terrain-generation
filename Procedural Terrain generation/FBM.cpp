#include "FBM.h"
#include "Math.h"

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

float FBM::Fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }
float FBM::Grad(int hash, float x) { return (hash & 1) == 0 ? x : -x; }
float FBM::Grad(int hash, float x, float y) { return ((hash & 1) == 0 ? x : -x) + ((hash & 2) == 0 ? y : -y); }

std::vector<float>GenerateNoiseMap()
{

}