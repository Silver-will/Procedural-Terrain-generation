#include "Terrain.h"
#include <iostream>
void Terrain::GenerateVertices()
{
    std::cout << map.noiseWidth << std::endl;
    for (int i = 0; i <= patchCount - 1; i++)
    {
        for (int j = 0; j <= patchCount - 1; j++)
        {
            vertices.push_back(-map.noiseWidth / 2.0f + map.noiseWidth * i / (float)patchCount); 
            vertices.push_back(0.0f); 
            vertices.push_back(-map.noiseHeight / 2.0f + map.noiseHeight * j / (float)patchCount); 
            vertices.push_back(i / (float)patchCount); 
            vertices.push_back(j / (float)patchCount); 

            vertices.push_back(-map.noiseWidth / 2.0f + map.noiseWidth * (i + 1) / (float)patchCount);
            vertices.push_back(0.0f);
            vertices.push_back(-map.noiseHeight / 2.0f + map.noiseHeight * j / (float)patchCount); 
            vertices.push_back((i + 1) / (float)patchCount); 
            vertices.push_back(j / (float)patchCount); 

            vertices.push_back(-map.noiseWidth / 2.0f + map.noiseWidth * i / (float)patchCount); 
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-map.noiseHeight / 2.0f + map.noiseHeight * (j + 1) / (float)patchCount);
            vertices.push_back(i / (float)patchCount); // u
            vertices.push_back((j + 1) / (float)patchCount); // v

            vertices.push_back(-map.noiseWidth / 2.0f + map.noiseWidth * (i + 1) / (float)patchCount); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-map.noiseHeight / 2.0f + map.noiseHeight * (j + 1) / (float)patchCount); // v.z
            vertices.push_back((i + 1) / (float)patchCount); // u
            vertices.push_back((j + 1) / (float)patchCount); // v
        }
    }

    glGenVertexArrays(1, &terrainVao);
    glGenBuffers(1, &terrainVbo);
    glBindVertexArray(terrainVao);
   
    glBindBuffer(GL_ARRAY_BUFFER, terrainVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glPatchParameteri(GL_PATCH_VERTICES, NUM_PATCH_PTS);

}

void Terrain::SetPatchCount(int patch)
{
    patchCount = patch;
}

void Terrain::Draw()
{
    glBindVertexArray(terrainVao);
    glDrawArrays(GL_PATCHES, 0, NUM_PATCH_PTS * patchCount * patchCount);
}

void Terrain::Update()
{
    if (map.ValueChanged())
    {
        map.GenerateNoiseMap();
        map.UpdateNoiseTexture();
    }
}

void Terrain::Cleanup()
{
    glDeleteVertexArrays(1, &terrainVao);
    glDeleteBuffers(1, &terrainVbo);
}

void Terrain::BindFBM()
{
    map.noisetexture.BindTexture();
}