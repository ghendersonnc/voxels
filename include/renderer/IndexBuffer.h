#pragma once
#include <vector>
#include <glad/glad.h>
namespace Voxels 
{
    class IndexBuffer {
    public:
        IndexBuffer();
        IndexBuffer(const std::vector<int>& indices, GLsizeiptr size);

        void setData(const std::vector<int>& indices, GLsizeiptr size);
        void bind();
        void unbind();
        void destroy();
    private:
        unsigned int mIndexBufferId;
    };
}