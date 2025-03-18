#pragma once

#include <unordered_map>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Camera.h"
#include "enums.h"
#include "Shader.h"

namespace Voxels

{
    class Sun {
    public:
        Sun();
        void draw(Camera& camera, std::unordered_map<ShaderProgram, Shader>& shaders);
    private:
        VertexArray mVertexArray;
        VertexBuffer mVertexBuffer;
        IndexBuffer mIndexBuffer;
    };
}
