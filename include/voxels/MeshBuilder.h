#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace Voxels 
{
    struct MeshBuilder {
        static int buildMesh(VertexBuffer& vbo, IndexBuffer& ebo, const std::vector<int>& chunkData);
    };

    
}