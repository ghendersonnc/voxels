#include "MeshBuilder.h"

#include <iostream>
#include <vector>

#include "Definitions.h"
#include "Vertex.h"
#include "Block.h"
#include "Blocks.h"

namespace Voxels
{
    void MeshBuilder::buildMesh(const std::vector<int>& chunkData, std::vector<Vertex>& vertices, std::vector<int>& indices, std::vector<int>& north, std ::vector<int>& south, std::vector<int>& east, std::vector<int>& west)
    {
        using namespace Definitions;
        constexpr int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
        vertices.reserve(CHUNK_VOLUME);
        unsigned int currentVertex = 0;
        for (short x = 0; x < CHUNK_SIZE; x++)
        {
            for (short z = 0; z < CHUNK_SIZE; z++)
            {
                for (short y = 0; y < CHUNK_SIZE; y++)
                {
                    
                    uint8_t cd = chunkData[x * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + y];
                    if (cd == 0)
                        continue;
                    
                    int directionIndex = x * CHUNK_SIZE * CHUNK_SIZE + (z-1) * CHUNK_SIZE + y;
                    bool pushFace = false;
                    if (z > 0 )
                        pushFace = chunkData[directionIndex] == 0;
                    else if (z == 0)
                        pushFace = north[x * CHUNK_SIZE * CHUNK_SIZE + (CHUNK_SIZE - 1) * CHUNK_SIZE + y] == 0;
                    constexpr float shadestuff = .5f;
                    const Block* block = &Blocks::blocks[cd];
                    if (pushFace)
                    {
                       // north side
                        vertices.emplace_back(x + 1, y + 0, z + 0, block->sideStartX, block->sideStartY, shadestuff, shadestuff, shadestuff);
                        vertices.emplace_back(x + 0, y + 0, z + 0, block->sideEndX, block->sideStartY, shadestuff, shadestuff, shadestuff);
                        vertices.emplace_back(x + 1, y + 1, z + 0, block->sideStartX, block->sideEndY);
                        vertices.emplace_back(x + 0, y + 1, z + 0, block->sideEndX, block->sideEndY);

                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 3);
                        indices.push_back(currentVertex + 1);
                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 2);
                        indices.push_back(currentVertex + 3);
                        currentVertex += 4;
                    }
                    directionIndex = x * CHUNK_SIZE * CHUNK_SIZE + (z+1) * CHUNK_SIZE + y;
                    pushFace = false;
                    if (z < CHUNK_SIZE - 1)
                        pushFace = chunkData[directionIndex] == 0;
                    else if (z == CHUNK_SIZE - 1)
                        pushFace = south[x * CHUNK_SIZE * CHUNK_SIZE + 0 * CHUNK_SIZE + y] == 0;
                    if (pushFace)
                    {
                        // south side
                        vertices.emplace_back(x + 0, y + 0, z + 1, block->sideStartX, block->sideStartY, shadestuff, shadestuff, shadestuff);
                        vertices.emplace_back(x + 1, y + 0, z + 1, block->sideEndX, block->sideStartY, shadestuff, shadestuff, shadestuff);
                        vertices.emplace_back(x + 0, y + 1, z + 1, block->sideStartX, block->sideEndY);
                        vertices.emplace_back(x + 1, y + 1, z + 1, block->sideEndX, block->sideEndY);

                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 3);
                        indices.push_back(currentVertex + 1);
                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 2);
                        indices.push_back(currentVertex + 3);
                        currentVertex += 4;
                    }

                    directionIndex = (x - 1) * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + y;
                    pushFace = false;
                    if ((x > 0 && x < CHUNK_SIZE - 1) || (directionIndex >= 0 && directionIndex < CHUNK_VOLUME))
                        pushFace = chunkData[directionIndex] == 0;
                    else if (x == 0)
                        pushFace = west[(CHUNK_SIZE - 1) * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + y] == 0;
                    if (pushFace)
                    {
                        // West side
                        vertices.emplace_back(x + 0, y + 0, z + 0, block->sideStartX, block->sideStartY, shadestuff, shadestuff, shadestuff);
                        vertices.emplace_back(x + 0, y + 0, z + 1, block->sideEndX, block->sideStartY, shadestuff, shadestuff, shadestuff);
                        vertices.emplace_back(x + 0, y + 1, z + 0, block->sideStartX, block->sideEndY);
                        vertices.emplace_back(x + 0, y + 1, z + 1, block->sideEndX, block->sideEndY);

                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 3);
                        indices.push_back(currentVertex + 1);
                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 2);
                        indices.push_back(currentVertex + 3);
                        currentVertex += 4;
                    }

                    directionIndex = (x + 1) * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + y;
                    pushFace = false;
                    if ((x > 0 && x < CHUNK_SIZE - 1) || (directionIndex >= 0 && directionIndex < CHUNK_VOLUME))
                        pushFace = chunkData[directionIndex] == 0;
                    else if (x == CHUNK_SIZE - 1)
                        pushFace = east[0 * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + y] == 0;
                    if (pushFace)
                    {
                        // East side    
                        vertices.emplace_back(x + 1, y + 0, z + 1, block->sideStartX, block->sideStartY, shadestuff, shadestuff, shadestuff);
                        vertices.emplace_back(x + 1, y + 0, z + 0, block->sideEndX, block->sideStartY, shadestuff, shadestuff, shadestuff);
                        vertices.emplace_back(x + 1, y + 1, z + 1, block->sideStartX, block->sideEndY);
                        vertices.emplace_back(x + 1, y + 1, z + 0, block->sideEndX, block->sideEndY);

                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 3);
                        indices.push_back(currentVertex + 1);
                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 2);
                        indices.push_back(currentVertex + 3);
                        currentVertex += 4;
                    }

                    directionIndex = x * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + (y-1);
                    pushFace = false;
                    if ((y > 0 && y < CHUNK_SIZE - 1) || (directionIndex >= 0 && directionIndex < CHUNK_VOLUME))
                        pushFace = chunkData[directionIndex] == 0;
                    if (y <= 0 || pushFace)
                    {
                        // Bottom side
                        vertices.emplace_back(x + 1, y + 0, z + 1, block->bottomStartX, block->bottomStartY);
                        vertices.emplace_back(x + 0, y + 0, z + 1, block->bottomEndX, block->bottomStartY);
                        vertices.emplace_back(x + 1, y + 0, z + 0, block->bottomStartX, block->bottomEndY);
                        vertices.emplace_back(x + 0, y + 0, z + 0, block->bottomEndX, block->bottomEndY);

                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 3);
                        indices.push_back(currentVertex + 1);
                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 2);
                        indices.push_back(currentVertex + 3);
                        currentVertex += 4;
                    }

                    directionIndex = x * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + (y+1);
                    pushFace = false;
                    if ((y > 0 && y < CHUNK_SIZE - 1) || (directionIndex >= 0 && directionIndex < CHUNK_VOLUME))
                        pushFace = chunkData[directionIndex] == 0;
                    if (y >= CHUNK_SIZE - 1 || pushFace)
                    {
                        // Top side
                        vertices.emplace_back(x + 0, y + 1, z + 1, block->topStartX, block->topStartY);
                        vertices.emplace_back(x + 1, y + 1, z + 1, block->topEndX, block->topStartY);
                        vertices.emplace_back(x + 0, y + 1, z + 0, block->topStartX, block->topEndY);
                        vertices.emplace_back(x + 1, y + 1, z + 0, block->topEndX, block->topEndY);

                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 3);
                        indices.push_back(currentVertex + 1);
                        indices.push_back(currentVertex + 0);
                        indices.push_back(currentVertex + 2);
                        indices.push_back(currentVertex + 3);
                        currentVertex += 4;
                    }
                }
            }
        }

    }
}
