#include "VertexArray.h"

#include <cassert>

namespace Voxels
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &mVertexArrayId);
    }

    void VertexArray::linkAttributes(VertexBuffer& vbo, const unsigned int layout, const int numberOfComponents, const GLenum type, const GLsizei stride, void* offset)
    {
        vbo.bind();
        assert(numberOfComponents <= 4 && numberOfComponents >= 1);

        glVertexAttribPointer(layout, numberOfComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        vbo.unbind();
    }

    void VertexArray::bind()
    {
        glBindVertexArray(mVertexArrayId);
    }

    void VertexArray::unbind()
    {
        glBindVertexArray(0);
    }

    void VertexArray::destroy()
    {
        glDeleteVertexArrays(1, &mVertexArrayId);
    }
}
