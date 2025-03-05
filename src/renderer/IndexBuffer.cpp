#include "IndexBuffer.h"
#include <iostream>
namespace Voxels
{
    IndexBuffer::IndexBuffer()
    {
        glGenBuffers(1, &mIndexBufferId);
    }

    IndexBuffer::IndexBuffer(const std::vector<int>& indices, const GLsizeiptr size)
    {
        glGenBuffers(1, &mIndexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), GL_STATIC_DRAW);
    }

    void IndexBuffer::setData(const std::vector<int>& indices, const GLsizeiptr size)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), GL_STATIC_DRAW);
    }

    void IndexBuffer::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
    }

    void IndexBuffer::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::destroy()
    {
        glDeleteBuffers(1, &mIndexBufferId);
    }
}
