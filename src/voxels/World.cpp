#include "World.h"

#include <iostream>


namespace Voxels
{
    World::World(const std::unordered_map<ShaderProgram, Shader>& shaders)
    {
        mShaders = shaders;
        mChunks.reserve(64);

        for (int i = -4; i < 4; i++)
        {
            for (int j = -4; j < 4; j++)
            {
                mChunks.emplace_back(glm::vec3(i, 0, j));
            }
        }
    }

    void World::render(Camera& camera)
    {
        mShaders[ChunkProgram].use();
        for (auto& chunk : mChunks)
        {
            chunk.draw(mShaders[ChunkProgram], camera);
        }
    }

    void World::cleanup()
    {
        for (auto& chunk : mChunks)
        {
            chunk.destroy();
        }

        for (auto& shader : mShaders)
        {
            shader.second.destroy();
        }
    }
}

