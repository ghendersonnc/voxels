#include "World.h"

#include <iostream>

#include "Definitions.h"

namespace Voxels
{
    World::World(const std::unordered_map<ShaderProgram, Shader>& shaders, const glm::vec3& cameraPosition) : mTexture(RESOURCE_PATH "textures/atlas.png", true)
    {
        using namespace Definitions;
        mShaders = shaders;
        
        constexpr uint8_t distance = RENDER_DISTANCE * 2 + 1;

        const auto chunkPositionX = static_cast<int>(cameraPosition.x) / static_cast<int>(CHUNK_SIZE);
        const auto chunkPositionZ = static_cast<int>(cameraPosition.z) / static_cast<int>(CHUNK_SIZE);
        for (int x = chunkPositionX - RENDER_DISTANCE; x <= chunkPositionX + RENDER_DISTANCE; x++)
        {
            for (int z = chunkPositionZ - RENDER_DISTANCE; z <= chunkPositionZ + RENDER_DISTANCE; z++)
            {
                std::tuple position{ x, 0, z };
                glm::vec3 pos = glm::vec3(x, 0, z);
                mChunks.try_emplace(position, pos);
            }
        }
    }

    void World::render(Camera& camera)
    {
        mTexture.bind();
        mShaders[ChunkProgram].use();
        for (auto& chunk : mChunks)
        {
            chunk.second.draw(mShaders[ChunkProgram], camera);
        }
    }

    void World::cleanup()
    {
        for (auto& chunk : mChunks)
        {
            chunk.second.destroy();
        }

        for (auto& shader : mShaders)
        {
            shader.second.destroy();
        }
    }
}

