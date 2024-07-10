#ifndef TERRAIN_H
#define TERRAIN_H
#include <vector>
#include
struct Terrain
{
	Terrain();
	void GenerateVertices(std::vector<float> noiseMap);
	void Draw(Shader& shader);
	void BindBuffers();
};

#endif

