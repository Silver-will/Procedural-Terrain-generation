#include "Terrain.h"

void Terrain::GenerateVertices(std::vector<float>& noiseMap, int width, int height)
{
    for (int i = 0; i <= patchCount - 1; i++)
    {
        for (int j = 0; j <= patchCount - 1; j++)
        {
            vertices.push_back(-width / 2.0f + width * i / (float)patchCount); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height / 2.0f + height * j / (float)patchCount); // v.z
            vertices.push_back(i / (float)patchCount); // u
            vertices.push_back(j / (float)patchCount); // v

            vertices.push_back(-width / 2.0f + width * (i + 1) / (float)patchCount); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height / 2.0f + height * j / (float)patchCount); // v.z
            vertices.push_back((i + 1) / (float)patchCount); // u
            vertices.push_back(j / (float)patchCount); // v

            vertices.push_back(-width / 2.0f + width * i / (float)patchCount); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height / 2.0f + height * (j + 1) / (float)patchCount); // v.z
            vertices.push_back(i / (float)patchCount); // u
            vertices.push_back((j + 1) / (float)patchCount); // v

            vertices.push_back(-width / 2.0f + width * (i + 1) / (float)patchCount); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height / 2.0f + height * (j + 1) / (float)patchCount); // v.z
            vertices.push_back((i + 1) / (float)patchCount); // u
            vertices.push_back((j + 1) / (float)patchCount); // v
        }
    }

    glGenVertexArrays(1, &terrainVao);
    glBindVertexArray(terrainVbo);

    glGenBuffers(1, &terrainVbo);
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
    glBindVertexArray(terrainVao);
    glDrawArrays(GL_PATCHES, 0, NUM_PATCH_PTS * patchCount * patchCount);
}

void Terrain::Cleanup()
{
    glDeleteVertexArrays(1, &terrainVao);
    glDeleteBuffers(1, &terrainVbo);
}