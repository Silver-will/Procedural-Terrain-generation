#ifndef TERRAIN_H
#define TERRAIN_H
#include <vector>
#include "Shader.h"
#include "FBM.h"

struct ErosionParams {
	uint32_t  mapSize = 256;
	uint32_t brushLength;
	uint32_t  borderSize = 3;
	uint32_t  maxLifetime = 30;
	float inertia = .9f;
	float sedimentCapacityFactor = 3;
	float minSedimentCapacity = 0.01f;
	float depositSpeed = .3f;
	float erodeSpeed = .3f;
	float evaportateSpeed = 0.01f;
	float gravity = 4;
	float startSpeed = 1;
	float startWater = 1;
};

struct Terrain
{
	Terrain(int width, int height):map(width, height) {};
	void GenerateVertices();
	void Draw();
	void SetPatchCount(int patch);
	void Update();
	void BindFBM();
	void Cleanup();
	FBM map;
	ErosionParams erosion;

private:
	
	GLuint terrainVao{}, terrainVbo{};
	GLuint NUM_PATCH_PTS = 4u;
	std::vector<float> vertices;
	int patchCount = 20;
};

#endif

