#include "World.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "Definitions.h"

namespace Voxels
{
    World::World(const std::unordered_map<ShaderProgram, Shader>& shaders) : mTexture(RESOURCE_PATH "textures/atlas.png", true)
    {
        mLastChunkPositionX = -1000000;
        mLastChunkPositionZ = -1000000;
        mActiveLoading = 0;
        mShaders = shaders;
        mLoaded = false;
        mSeed = static_cast<long long>(glfwGetTime());
    }

    World::~World()
    {
        for (auto& shader : mShaders)
        {
            shader.second.destroy();
        }
    }

    void World::update(const glm::vec3& cameraPosition)
    {
        using namespace Definitions;
        const auto chunkPositionX = static_cast<int>(cameraPosition.x) / static_cast<int>(CHUNK_SIZE);
        const auto chunkPositionZ = static_cast<int>(cameraPosition.z) / static_cast<int>(CHUNK_SIZE);


        if (chunkPositionX != mLastChunkPositionX || chunkPositionZ != mLastChunkPositionZ)
        {
            mLastChunkPositionX = chunkPositionX;
            mLastChunkPositionZ = chunkPositionZ;
                                                
            while (!mChunkQueue.empty())
                mChunkQueue.pop();

            mLoaded = false;
        }

        if (!mLoaded)
        {
            mChunkQueue.emplace(chunkPositionX, 0, chunkPositionZ); // center chunk
            for (int renderDistance = 1; renderDistance <= RENDER_DISTANCE; renderDistance++)
            {

                // begin cardinals
                mChunkQueue.emplace(chunkPositionX, 0, chunkPositionZ - renderDistance);
                mChunkQueue.emplace(chunkPositionX + renderDistance, 0, chunkPositionZ);
                mChunkQueue.emplace(chunkPositionX, 0, chunkPositionZ + renderDistance);
                mChunkQueue.emplace(chunkPositionX - renderDistance, 0, chunkPositionZ);
                // end cardinals

                for (int j = 1; j <= renderDistance; j++)
                {
                    mChunkQueue.emplace(chunkPositionX - j, 0, chunkPositionZ + renderDistance);
                    mChunkQueue.emplace(chunkPositionX + j, 0, chunkPositionZ + renderDistance);

                    if (j < renderDistance)
                    {
                        mChunkQueue.emplace(chunkPositionX + renderDistance, 0, chunkPositionZ - j);
                        mChunkQueue.emplace(chunkPositionX + renderDistance, 0, chunkPositionZ + j);

                        mChunkQueue.emplace(chunkPositionX - renderDistance, 0, chunkPositionZ - j);
                        mChunkQueue.emplace(chunkPositionX - renderDistance, 0, chunkPositionZ + j);
                    }

                    mChunkQueue.emplace(chunkPositionX - j, 0, chunkPositionZ - renderDistance);
                    mChunkQueue.emplace(chunkPositionX + j, 0, chunkPositionZ - renderDistance);
                }
            }
            constexpr int16_t distance = RENDER_DISTANCE * 2 + 1;
            assert(static_cast<int>(mChunkQueue.size()) == distance * distance);
            mLoaded = true;
        } else if (!mChunkQueue.empty())
        {
            glm::vec3 position = mChunkQueue.front();
            mChunkQueue.pop();

            std::tuple positionTuple{ position.x, position.y, position.z };

            mChunks.try_emplace(positionTuple, position, mSeed);
        }
    }

    void World::render(Camera& camera)
    {
        mTexture.bind();
        mShaders[ChunkProgram].use();
        for (auto chunk = mChunks.begin(); chunk != mChunks.end();)
        {
            if (
                abs(static_cast<int>(chunk->second.chunkPosition.x) - mLastChunkPositionX) > Definitions::RENDER_DISTANCE ||
                abs(static_cast<int>(chunk->second.chunkPosition.z) - mLastChunkPositionZ) > Definitions::RENDER_DISTANCE
                )
            {
                chunk = mChunks.erase(chunk);
            }
            else
            {
                chunk->second.draw(mShaders[ChunkProgram], camera);
                ++chunk;
            }
        }
    }
}

