#ifndef TERRAIN_H
#define TERRAIN_H
#include <vector>
#include "Shader.h"
#include "FBM.h"
#include "Lighting.h"
#include <array>

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

struct ErosionBuffer{
	std::array<float, 7> brush_indices;
	std::array<float, 7> brush_weights;
	std::array<float, 256 * 256> map;
	std::vector<int> random_indices;
};

struct Terrain
{
	Terrain(int width, int height);
	void GenerateVertices();
	void Draw(Shader& shader);
	void SetPatchCount(int patch);
	void UpdateValues(Shader& shad);
	void Update(Shader& shader);
	void BindFBM();
	void Cleanup();
	FBM map;
	ErosionParams erosion;
	Lighting direct;
	float maxTess, minTess;
	float maxDistance, minDistance;
	float height;

private:
	
	GLuint terrainVao{}, terrainVbo{};
	GLuint NUM_PATCH_PTS = 4u;
	std::vector<float> vertices;
	int patchCount = 20;
};

#endif

