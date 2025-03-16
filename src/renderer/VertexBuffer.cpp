#include "VertexBuffer.h"

#include "Vertex.h"
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

    template <typename T>
    void VertexBuffer::setData(const std::vector<T>& vertices, const GLsizeiptr size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
    }

    template void VertexBuffer::setData<int8_t>(const std::vector<int8_t>& vertices, GLsizeiptr size);
    template void VertexBuffer::setData<Vertex>(const std::vector<Vertex>& vertices, GLsizeiptr size);
    template void VertexBuffer::setData<float>(const std::vector<float>& vertices, GLsizeiptr size);

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
