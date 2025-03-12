#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace Voxels 
{
    struct MeshBuilder {
        static void buildMesh(const std::vector<int>& chunkData, std::vector<Vertex>& vertices,
                              std::vector<int>& indices);
    };

    
}