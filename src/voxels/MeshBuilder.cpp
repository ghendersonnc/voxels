#include "MeshBuilder.h"

#include <iostream>
#include <vector>

#include "Definitions.h"
#include "Vertex.h"
#include "Block.h"
#include "Blocks.h"

namespace Voxels
{
    int MeshBuilder::buildMesh(VertexBuffer& vbo, IndexBuffer& ebo, const std::vector<int>& chunkData)
    {
        std::vector<Vertex> vertices;
        constexpr int CHUNK_VOLUME = Definitions::CHUNK_SIZE * Definitions::CHUNK_SIZE * Definitions::CHUNK_SIZE;
        vertices.reserve(CHUNK_VOLUME);
        // NOLINT(bugprone-implicit-widening-of-multiplication-result)
        std::vector<int> indices;
        unsigned int currentVertex = 0;
        for (short x = 0; x < Definitions::CHUNK_SIZE; x++)
        {
            for (short z = 0; z < Definitions::CHUNK_SIZE; z++)
            {
                for (short y = 0; y < Definitions::CHUNK_SIZE; y++)
                {
                    
                    uint8_t cd = chunkData[x * Definitions::CHUNK_SIZE * Definitions::CHUNK_SIZE + z * Definitions::CHUNK_SIZE + y];
                    if (cd == 0)
                        continue;
                    
                    int directionIndex = x * Definitions::CHUNK_SIZE * Definitions::CHUNK_SIZE + (z-1) * Definitions::CHUNK_SIZE + y;
                    bool doBlock = false;
                    if ((z > 0 && z < Definitions::CHUNK_SIZE - 1) || (directionIndex >= 0 && directionIndex < CHUNK_VOLUME))
                        doBlock = chunkData[directionIndex] == 0;

                    const Block* block = &Blocks::blocks[cd];
                    if (z <= 0 || doBlock)
                    {
                       // north side
                        vertices.emplace_back(x + 1, y + 0, z + 0, block->sideStartX, block->sideStartY);
                        vertices.emplace_back(x + 0, y + 0, z + 0, block->sideEndX, block->sideStartY);
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
                    directionIndex = x * Definitions::CHUNK_SIZE * Definitions::CHUNK_SIZE + (z+1) * Definitions::CHUNK_SIZE + y;
                    doBlock = false;
                    if ((z > 0 && z < Definitions::CHUNK_SIZE - 1) || (directionIndex >= 0 && directionIndex < CHUNK_VOLUME))
                        doBlock = chunkData[directionIndex] == 0;
                    if (z >= Definitions::CHUNK_SIZE - 1 || doBlock)
                    {
                        // south side
                        vertices.emplace_back(x + 0, y + 0, z + 1, block->sideStartX, block->sideStartY);
                        vertices.emplace_back(x + 1, y + 0, z + 1, block->sideEndX, block->sideStartY);
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

                    directionIndex = (x-1) * Definitions::CHUNK_SIZE * Definitions::CHUNK_SIZE + z * Definitions::CHUNK_SIZE + y;
                    doBlock = false;
                    if ((x > 0 && x < Definitions::CHUNK_SIZE - 1) || (directionIndex >= 0 && directionIndex < CHUNK_VOLUME))
                        doBlock = chunkData[directionIndex] == 0;
                    if (x <= 0 || doBlock)
                    {
                        // West side
                        vertices.emplace_back(x + 0, y + 0, z + 0, block->sideStartX, block->sideStartY);
                        vertices.emplace_back(x + 0, y + 0, z + 1, block->sideEndX, block->sideStartY);
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

                    directionIndex = (x+1) * Definitions::CHUNK_SIZE * Definitions::CHUNK_SIZE + z * Definitions::CHUNK_SIZE + y;
                    doBlock = false;
                    if ((x > 0 && x < Definitions::CHUNK_SIZE - 1) || (directionIndex >= 0 && directionIndex < CHUNK_VOLUME))
                        doBlock = chunkData[directionIndex] == 0;
                    if (x >= Definitions::CHUNK_SIZE - 1 || doBlock)
                    {
                        // East side    
                        vertices.emplace_back(x + 1, y + 0, z + 1, block->sideStartX, block->sideStartY);
                        vertices.emplace_back(x + 1, y + 0, z + 0, block->sideEndX, block->sideStartY);
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

                    directionIndex = x * Definitions::CHUNK_SIZE * Definitions::CHUNK_SIZE + z * Definitions::CHUNK_SIZE + (y-1);
                    doBlock = false;
                    if ((y > 0 && y < Definitions::CHUNK_SIZE - 1) || (directionIndex >= 0 && directionIndex < CHUNK_VOLUME))
                        doBlock = chunkData[directionIndex] == 0;
                    if (y <= 0 || doBlock)
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

                    directionIndex = x * Definitions::CHUNK_SIZE * Definitions::CHUNK_SIZE + z * Definitions::CHUNK_SIZE + (y+1);
                    doBlock = false;
                    if ((y > 0 && y < Definitions::CHUNK_SIZE - 1) || (directionIndex >= 0 && directionIndex < CHUNK_VOLUME))
                        doBlock = chunkData[directionIndex] == 0;
                    if (y >= Definitions::CHUNK_SIZE - 1 || doBlock)
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

        vbo.setData(vertices, sizeof(Vertex) * vertices.size());
        ebo.setData(indices, sizeof(float) * indices.size());
        return indices.size();
    }
}
