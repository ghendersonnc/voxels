#include "World.h"

#include <iostream>
#include "Definitions.h"

namespace Voxels
{
    World::World(const std::unordered_map<ShaderProgram, Shader>& shaders) : mTexture(RESOURCE_PATH "textures/atlas.png", true)
    {
        activeLoading = 0;
        mShaders = shaders;
        loaded = false;
    }

    void World::update(const glm::vec3& cameraPosition)
    {
        using namespace Definitions;
        // TODO: check if camera enters new chunk, thus needing to generate new chunks and delete out-of-distance chunks

        constexpr uint8_t distance = RENDER_DISTANCE * 2 + 1;

        const auto chunkPositionX = static_cast<int>(cameraPosition.x) / static_cast<int>(CHUNK_SIZE);
        const auto chunkPositionZ = static_cast<int>(cameraPosition.z) / static_cast<int>(CHUNK_SIZE);
        if (!loaded)
        {
            for (int x = chunkPositionX - RENDER_DISTANCE; x <= chunkPositionX + RENDER_DISTANCE; x++)
            {
                for (int z = chunkPositionZ - RENDER_DISTANCE; z <= chunkPositionZ + RENDER_DISTANCE; z++)
                {
                    chunkQueue.emplace(x, 0, z);
                }
            }
            loaded = true;
        } else if (!chunkQueue.empty())
        {
            glm::vec3 position = chunkQueue.front();
            chunkQueue.pop();

            std::tuple positionTuple{ position.x, position.y, position.z };

            mChunks.try_emplace(positionTuple, position);
        }
    }

    void World::render(Camera& camera)
    {
        mTexture.bind();
        mShaders[ChunkProgram].use();
        for (auto& [coords, chunk] : mChunks)
        {
            chunk.draw(mShaders[ChunkProgram], camera);
        }
    }

    void World::cleanup()
    {
        for (auto& shader : mShaders)
        {
            shader.second.destroy();
        }
    }
}

