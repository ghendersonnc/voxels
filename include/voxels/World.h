#pragma once

#include <queue>
#include <unordered_map>
#include <tuple>

#include <glm/glm.hpp>

#include "Camera.h"
#include "Camera.h"
#include "Camera.h"
#include "Chunk.h"
#include "Shader.h"
#include "enums.h"
#include "Texture.h"
#include "Hash.h"

namespace Voxels
{
    class World {
    public:
        World(const std::unordered_map<ShaderProgram, Shader>& shaders);
        ~World();
        void update(Camera& camera);
        void render(Camera& camera);

    private:
        std::unordered_map<ShaderProgram, Shader> mShaders;
        std::unordered_map<std::tuple<int,int,int>, Chunk> mChunks;
        std::queue<glm::vec3> mChunkQueue;
        int mActiveLoading;
        Texture mTexture;
        bool mLoaded;
        long long mSeed;

        int mLastChunkPositionX, mLastChunkPositionZ;
    };
}