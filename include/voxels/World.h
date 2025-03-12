#pragma once

#include <vector>
#include <unordered_map>
#include <tuple>

#include <glm/glm.hpp>

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
        World(const std::unordered_map<ShaderProgram, Shader>& shaders, const glm::vec3& cameraPosition);
        void update();
        void render(Camera& camera);
        void cleanup();
    private:
        std::unordered_map<ShaderProgram, Shader> mShaders;
        std::unordered_map<std::tuple<int,int,int>, Chunk> mChunks;
        Texture mTexture;
    };
}