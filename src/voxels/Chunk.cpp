#include "Chunk.h"

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "OpenSimplexNoise.hpp"

#include "Definitions.h"
#include "MeshBuilder.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"



namespace Voxels
{

    int maxHeightGen()
    {
        return rand() % Definitions::CHUNK_SIZE;
    }

    Chunk::Chunk()
    {
        mVertexArray.bind();
        mMeshData.reserve(Definitions::CHUNK_SIZE * Definitions::CHUNK_SIZE * Definitions::CHUNK_SIZE);
        OpenSimplexNoise noise;
        for (short x = 0; x < Definitions::CHUNK_SIZE; x++)
        {
            
            for (short z = 0; z < Definitions::CHUNK_SIZE; z++)
            {
                int noiseY = (noise.Evaluate(x * .1f, z * .1f) * 3.0f) + 20;
                for (short y = 0; y < Definitions::CHUNK_SIZE; y++)
                {
                    if (y <= noiseY)
                        mMeshData.push_back(1);
                    else
                        mMeshData.push_back(0);
                }
            }
        }
        elementCount = MeshBuilder::buildMesh(mVertexBuffer, mIndexBuffer, mMeshData);
        
        mVertexArray.linkAttributes(mVertexBuffer, 0, 3, GL_BYTE, sizeof(Vertex), nullptr);
        mVertexArray.linkAttributes(mVertexBuffer, 1, 2, GL_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, texturePosition));
    }

    void Chunk::draw(Shader& shader)
    {
        
        mVertexArray.bind();
        mIndexBuffer.bind();
        shader.use();

        auto model = glm::mat4(1.0f);
        auto view = glm::mat4(1.0f);
        auto projection = glm::mat4(1.0f);
        float time = static_cast<float>(glfwGetTime());
        model = glm::rotate(model, 0.5f, glm::vec3(1.5f, .5f, 0.5f));
        view = glm::translate(view, glm::vec3(-10.0f, -10.0f, -70.0f));
        projection = glm::perspective(glm::radians(45.0f), static_cast<float>(Definitions::SCREEN_WIDTH) / static_cast<float>(Definitions::SCREEN_HEIGHT), 0.1f, 100.f);

        shader.setUniformMat4f("model", model);
        shader.setUniformMat4f("view", view);
        shader.setUniformMat4f("projection", projection);
        auto color = glm::vec4(1.0f, 0.0f, 0.f, 1.0f);
        color.x *= sin(time);
        shader.setUniform4f("uColor", color);
        glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
    }

    

}
