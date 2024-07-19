#ifndef TERRAIN_H
#define TERRAIN_H
#include <vector>
#include "Shader.h"
#include "FBM.h"
struct Terrain
{
	Terrain(int width, int height):map(width, height) {};
	void GenerateVertices();
	void Draw();
	void SetPatchCount(int patch);
	void Update();
	void Cleanup();

private:
	FBM map;
	GLuint terrainVao{}, terrainVbo{};
	GLuint NUM_PATCH_PTS = 4u;
	std::vector<float> vertices;
	int patchCount = 20;
};

#endif

