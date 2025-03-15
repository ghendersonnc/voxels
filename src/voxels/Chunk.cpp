#include "Chunk.h"

#include <GLFW/glfw3.h>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "OpenSimplexNoise.hpp"


#include "Definitions.h"
#include "MeshBuilder.h"
#include "enums.h"
#include "spdlog/spdlog.h"


namespace Voxels
{
    Chunk::Chunk(glm::vec3 chunkPosition_, long long& seed)
    {
        using namespace Definitions;
        mCanRender = false;
        ready = false;
        chunkPosition = chunkPosition_;
        mPositionInWorld = glm::vec3(chunkPosition.x * CHUNK_SIZE, chunkPosition.y * CHUNK_SIZE, chunkPosition.z * CHUNK_SIZE);

        
        mChunkThread = std::thread(&Chunk::generate, this, std::ref(seed));
        
    }

    Chunk::~Chunk()
    {
        if (mChunkThread.joinable())
            mChunkThread.join();

        mVertexBuffer.destroy();
        mVertexArray.destroy();
        mIndexBuffer.destroy();
    }

    void Chunk::generate(const long long& seed)   
    {
        using namespace Definitions;
        constexpr int chunkVolume = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
        mChunkData.reserve(chunkVolume);
        OpenSimplexNoise noise(seed);

        const int noiseEvalX = CHUNK_SIZE * static_cast<int>(chunkPosition.x);
        const int noiseEvalY = CHUNK_SIZE * static_cast<int>(chunkPosition.y);
        const int noiseEvalZ = CHUNK_SIZE * static_cast<int>(chunkPosition.z);
        
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                constexpr float frequency = .1f;
                constexpr float amplitude = 3.0f;
                constexpr int8_t yMax = 20;
                const float evalX = (static_cast<float>(x) + static_cast<float>(noiseEvalX)) * frequency;
                const float evalY = (static_cast<float>(z) + static_cast<float>(noiseEvalZ)) * frequency;
                const int noiseY = static_cast<int>(noise.Evaluate(evalX, evalY) * amplitude + yMax);
                const int noiseBiome = static_cast<int>(noise.Evaluate(evalX, evalY) * 5.0 + yMax);
                
                for (int y = 0; y < CHUNK_SIZE; y++)
                {
                    const float evalZ = (static_cast<float>(y) + static_cast<float>(noiseEvalY)) * frequency;
                    const int noiseCave = static_cast<int>(noise.Evaluate(evalX, evalY, evalZ) * 5.0);

                    if (y > noiseY || (y < noiseY - 3 && noiseCave <= 0 && y > 0))
                        mChunkData.push_back(Air);
                    else if (y == noiseY)
                    {
                        if (noiseBiome >= 19)
                            mChunkData.push_back(Grass);
                        else if (noiseBiome < 19)
                            mChunkData.push_back(Sand);
                        
                    }
                    else if (y <= noiseY - 1 && y >= noiseY - 2)
                        mChunkData.push_back(Dirt);
                    else if (y <= noiseY - 3 || y == 0)
                        mChunkData.push_back(Stone);
                    
                }
            }
        }
        MeshBuilder::buildMesh(mChunkData, vertices, indices);
        mElementCount = static_cast<int>(indices.size());
        mCanRender = true;
    }

    void Chunk::draw(const Shader& shader, const Camera& camera)
    {

        if (!ready)
        {
            if (mCanRender)
            {
                mVertexArray.bind();

                mVertexBuffer.setData(vertices, sizeof(Vertex) * vertices.size());
                mIndexBuffer.setData(indices, sizeof(int) * indices.size());

                mVertexArray.linkAttributes(mVertexBuffer, 0, 3, GL_BYTE, sizeof(Vertex),
                    (void*)offsetof(Vertex, vertexPosition));
                mVertexArray.linkAttributes(mVertexBuffer, 1, 2, GL_BYTE, sizeof(Vertex),
                    (void*)offsetof(Vertex, texturePosition));
                mVertexArray.linkAttributes(mVertexBuffer, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, colorValue));

                vertices.clear();
                vertices.shrink_to_fit();
                indices.clear();
                indices.shrink_to_fit();
                if (mChunkThread.joinable())
                    mChunkThread.join();

                ready = true;
            }
            return;
        }

        mVertexArray.bind();
        mIndexBuffer.bind();

        auto model = glm::mat4(1.0f);
        model = glm::translate(model, mPositionInWorld);
        const auto view = glm::lookAt(camera.position, camera.position + camera.front, camera.up);
        const auto projection = glm::perspective(glm::radians(camera.fov),
                                           static_cast<float>(Definitions::SCREEN_WIDTH) / static_cast<float>(
                                               Definitions::SCREEN_HEIGHT), 0.1f, 1000.f);

        shader.setUniformMat4f("model", model);
        shader.setUniformMat4f("view", view);
        shader.setUniformMat4f("projection", projection);
                
        glDrawElements(GL_TRIANGLES, mElementCount, GL_UNSIGNED_INT, nullptr);
    }

}
