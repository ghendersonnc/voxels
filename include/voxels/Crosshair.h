#pragma once

#include <unordered_map>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "enums.h"
#include "Texture.h"  

namespace Voxels
{
    class Crosshair {
    public:
        Crosshair();
        void draw(std::unordered_map<ShaderProgram, Shader>& shaders);
    private:
        VertexArray mVertexArray;
        VertexBuffer mVertexBuffer;
        IndexBuffer mIndexBuffer;
        Texture mTexture;
    };
}