#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
namespace Voxels 
{
    class Chunk {
    public:
        Chunk();
        void draw(Shader& shader);
        void rebuild();
    private:
        VertexArray mVertexArray;
        VertexBuffer mVertexBuffer;
        IndexBuffer mIndexBuffer;
        std::vector<int> mMeshData;

        int elementCount;
    };
}