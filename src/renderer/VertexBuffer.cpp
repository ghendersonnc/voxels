#include "VertexBuffer.h"

#include <iostream>
#include "MeshBuilder.h"

namespace Voxels
{
    VertexBuffer::VertexBuffer()
    {
        glGenBuffers(1, &mVertexBufferId);
    }

    VertexBuffer::VertexBuffer(const std::vector<float>& vertices, const GLsizeiptr size)
    {
        glGenBuffers(1, &mVertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
    }

    void VertexBuffer::setData(const std::vector<Vertex>& vertices, const GLsizeiptr size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
    }

    void VertexBuffer::setData(const std::vector<float>& vertices, const GLsizeiptr size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
    }

    void VertexBuffer::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    }

    void VertexBuffer::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    void VertexBuffer::destroy()
    {
        glDeleteBuffers(1, &mVertexBufferId);
    }
}
