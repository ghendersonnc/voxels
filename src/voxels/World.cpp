#include "World.h"

#include <iostream>


namespace Voxels
{
    World::World(const std::unordered_map<ShaderProgram, Shader>& shaders) : mTexture(RESOURCE_PATH "textures/atlas.png", true)
    {
        mShaders = shaders;
        mChunks.reserve(256);

        for (int x = -4; x < 4; x++)
        {
            for (int z = -4; z < 4; z++)
            {
                for (int y = -7; y < 1; y++)
                {
                    mChunks.emplace_back(glm::vec3(x, y, z));
                }
            }
        }
    }

    void World::render(Camera& camera)
    {
        mTexture.bind();
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

