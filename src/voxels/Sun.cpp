#include "Sun.h"

template<typename T>
void asdf(std::vector<T>& x)
{
    
}

namespace Voxels
{
    Sun::Sun()
    {
        std::vector<int8_t> vertices{
            1, 1, // top right
            1, -1, // bottom right
            -1, -1, // bottom left
            -1, 1, // top left 
        };

        std::vector indices{
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };
        mVertexArray.bind();
        
        mVertexBuffer.setData(vertices, sizeof(uint8_t) * vertices.size());
        mIndexBuffer.setData(indices, sizeof(int) * indices.size());
        mVertexArray.linkAttributes(mVertexBuffer, 0, 2, GL_BYTE, 2 * sizeof(int8_t), nullptr);
    }

    void Sun::draw(Camera& camera, std::unordered_map<ShaderProgram, Shader>& shaders)
    {
        shaders[SunProgram].use();
        mVertexArray.bind();
        mIndexBuffer.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

}
