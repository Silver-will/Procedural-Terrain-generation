#include "Terrain.h"
#include <iostream>

Terrain::Terrain(int width, int height) :map(width, height)
{
    minDistance = 20;
    maxDistance = 800;

    minTess = 4;
    maxTess = 64;

    this->height = 5.0f;
}


void Terrain::GenerateVertices()
{
    for (int i = 0; i <= patchCount - 1; i++)
    {
        for (int j = 0; j <= patchCount - 1; j++)
        {
            vertices.push_back(( - map.noiseWidth / 2.0f + map.noiseWidth * i / (float)patchCount)/10.0f);
            vertices.push_back(0.0f); 
            vertices.push_back((-map.noiseHeight / 2.0f + map.noiseHeight * j / (float)patchCount) / 10.0f);
            vertices.push_back(i / (float)patchCount); 
            vertices.push_back(j / (float)patchCount); 

            vertices.push_back((-map.noiseWidth / 2.0f + map.noiseWidth * (i + 1) / (float)patchCount) / 10.0f);
            vertices.push_back(0.0f);
            vertices.push_back((-map.noiseHeight / 2.0f + map.noiseHeight * j / (float)patchCount) / 10.0f);
            vertices.push_back((i + 1) / (float)patchCount); 
            vertices.push_back(j / (float)patchCount); 

            vertices.push_back((-map.noiseWidth / 2.0f + map.noiseWidth * i / (float)patchCount) / 10.0f);
            vertices.push_back(0.0f); // v.y
            vertices.push_back((-map.noiseHeight / 2.0f + map.noiseHeight * (j + 1) / (float)patchCount) / 10.0f);
            vertices.push_back(i / (float)patchCount); // u
            vertices.push_back((j + 1) / (float)patchCount); // v

            vertices.push_back((-map.noiseWidth / 2.0f + map.noiseWidth * (i + 1) / (float)patchCount) / 10.0f); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(( - map.noiseHeight / 2.0f + map.noiseHeight * (j + 1) / (float)patchCount) / 10.0f); // v.z
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

void Terrain::Draw(Shader& shader)
{
    Update(shader);
    glBindVertexArray(terrainVao);
    glDrawArrays(GL_PATCHES, 0, NUM_PATCH_PTS * patchCount * patchCount);
}

void Terrain::Update(Shader& shader)
{
    UpdateValues(shader);
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

void Terrain::UpdateValues(Shader& shad)
{
    //Update tessellation values
    shad.SetVector2f("distance", glm::vec2(minDistance, maxDistance), false);
    shad.SetVector2f("tess_level", glm::vec2(minTess, maxTess), false);
    shad.SetFloat("height", height, false);
    //Update lighting values too
    direct.UploadLightValues(shad);
}