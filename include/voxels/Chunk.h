#pragma once

#include <thread>

#include <glm/glm.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Vertex.h"

namespace Voxels 
{
    class Chunk {
    public:
        Chunk() = default;
        Chunk(glm::vec3 chunkPosition);
        ~Chunk();
        void generate();
        void draw(Shader& shader, Camera& camera);
        void rebuild();

    private:
        VertexArray mVertexArray;
        VertexBuffer mVertexBuffer;
        IndexBuffer mIndexBuffer;
        std::vector<int> mChunkData;
        std::vector<Vertex> vertices;
        std::vector<int> indices;
        glm::vec3 mPositionInWorld;
        glm::vec3 mChunkPosition;

        int mElementCount;
        bool mCanRender;
        bool ready;
        std::thread mChunkThread;
    };
}