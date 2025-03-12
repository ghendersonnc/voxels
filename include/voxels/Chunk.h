#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"

namespace Voxels 
{
    class Chunk {
    public:
        Chunk() = default;
        Chunk(glm::vec3 chunkPosition);

        void draw(Shader& shader, Camera& camera);
        void rebuild();
        void destroy();
    private:
        VertexArray mVertexArray;
        VertexBuffer mVertexBuffer;
        IndexBuffer mIndexBuffer;
        std::vector<int> mChunkData;
        glm::vec3 mPositionInWorld;

        int mElementCount;
        bool canRender;
        glm::vec3 mChunkPosition;

    };
}