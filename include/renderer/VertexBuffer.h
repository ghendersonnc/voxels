#pragma once

#include <vector>

#include <glad/glad.h>

#include "Vertex.h"

namespace Voxels
{
    class VertexBuffer
    {
    public:
        VertexBuffer();
        VertexBuffer(const std::vector<float>& vertices, GLsizeiptr size);

        template <typename T>
        void setData(const std::vector<T>& vertices, GLsizeiptr size);

        void bind();
        void unbind();
        void destroy();

    private:
        GLuint mVertexBufferId;
    };
}
