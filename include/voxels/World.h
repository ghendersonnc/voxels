#pragma once

#include <vector>
#include <unordered_map>

#include "Camera.h"
#include "Chunk.h"
#include "Shader.h"
#include "enums.h"
#include "Texture.h"

namespace Voxels
{
    class World {
    public:
        World(const std::unordered_map<ShaderProgram, Shader>& shaders);
        void update();
        void render(Camera& camera);
        void cleanup();
    private:
        std::unordered_map<ShaderProgram, Shader> mShaders;
        std::vector<Chunk> mChunks;
        Texture mTexture;
    };
}