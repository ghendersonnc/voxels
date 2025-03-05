#pragma once
#include "VertexBuffer.h"
namespace Voxels
{
    class VertexArray
    {
    public:
        VertexArray();
        void linkAttributes(VertexBuffer& vbo, const unsigned int layout, const int numberOfComponents, const GLenum type, GLsizei stride, void* offset);
        void bind();
        void unbind();
        void destroy();
    private:
        unsigned int mVertexArrayId;
    };
}