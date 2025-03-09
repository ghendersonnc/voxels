#include "Chunk.h"

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <GLFW/glfw3.h>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "OpenSimplexNoise.hpp"

#include "Definitions.h"
#include "MeshBuilder.h"
#include "enums.h"


namespace Voxels
{
    Chunk::Chunk(const glm::vec3 chunkPosition)
    {
        using namespace Definitions;
        mChunkPosition = chunkPosition;
        mPositionInWorld = glm::vec3(chunkPosition.x * CHUNK_SIZE, chunkPosition.y * CHUNK_SIZE, chunkPosition.z * CHUNK_SIZE);
        mVertexArray.bind();
        mChunkData.reserve(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
        OpenSimplexNoise noise;

        int noiseEvalX = CHUNK_SIZE * chunkPosition.x;
        int noiseEvalZ = CHUNK_SIZE * chunkPosition.z;

        // changing this number is fun
        const float depth = 3.f;
        for (short x = 0; x < CHUNK_SIZE; x++)
        {
            
            for (short z = 0; z < CHUNK_SIZE; z++)
            {
                int noiseY = (noise.Evaluate((x+noiseEvalX) * .1f, (z+noiseEvalZ) * .1f) * depth) + 20;
                for (short y = 0; y < CHUNK_SIZE; y++)
                {
                    if (y > noiseY)
                        mChunkData.push_back(Air);
                    else if (y == noiseY)
                        mChunkData.push_back(Grass);
                    else if (y > noiseY - 3 && y < noiseY)
                        mChunkData.push_back(Dirt);
                    else if (y <= noiseY - 3)
                        mChunkData.push_back(Stone);
                }
            }
        }
        mElementCount = MeshBuilder::buildMesh(mVertexBuffer, mIndexBuffer, mChunkData);
        
        mVertexArray.linkAttributes(mVertexBuffer, 0, 3, GL_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, vertexPosition));
        mVertexArray.linkAttributes(mVertexBuffer, 1, 2, GL_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, texturePosition));
    }

    void Chunk::draw(Shader& shader, Camera& camera)
    {
        
        mVertexArray.bind();
        mIndexBuffer.bind();

        auto model = glm::mat4(1.0f);
        auto view = glm::mat4(1.0f);
        auto projection = glm::mat4(1.0f);
        float time = static_cast<float>(glfwGetTime());
        model = glm::translate(model,mPositionInWorld);
        view = glm::lookAt(camera.position, camera.position + camera.front, camera.up);
        projection = glm::perspective(glm::radians(camera.fov), static_cast<float>(Definitions::SCREEN_WIDTH) / static_cast<float>(Definitions::SCREEN_HEIGHT), 0.1f, 300.f);

        shader.setUniformMat4f("model", model);
        shader.setUniformMat4f("view", view);
        shader.setUniformMat4f("projection", projection);
                
        glDrawElements(GL_TRIANGLES, mElementCount, GL_UNSIGNED_INT, nullptr);
    }

    void Chunk::destroy()
    {
        mVertexBuffer.destroy();
        mVertexArray.destroy();
        mIndexBuffer.destroy();
    }
}
