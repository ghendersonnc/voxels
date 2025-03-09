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

        void setData(const std::vector<Vertex>& vertices, GLsizeiptr size);
        void setData(const std::vector<float>& vertices, GLsizeiptr size);
        void bind();
        void unbind();
        void destroy();

    private:
        GLuint mVertexBufferId;
    };
}
