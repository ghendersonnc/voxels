#include "Crosshair.h"

#include <vector>

#include "Definitions.h"


namespace Voxels
{
    Crosshair::Crosshair() : mTexture(RESOURCE_PATH "textures/crosshair.png", false)
    {
        using namespace Definitions;

        float aspect = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);
        float x = 0.04f;
        float y = x * aspect;
        std::vector vertices{
            x, y,1.f, 1.f, // top right
            x, -y, 1.f, 0.f, // bottom right
            -x, -y,0.f,0.f, // bottom left
            -x, y,0.f, 1.f // top left 
        };

        std::vector indices{
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };
        mVertexArray.bind();
        mVertexBuffer.setData(vertices, sizeof(float) * vertices.size());
        mIndexBuffer.setData(indices, sizeof(int) * indices.size());
        mVertexArray.linkAttributes(mVertexBuffer, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
        mVertexArray.linkAttributes(mVertexBuffer, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2*sizeof(float)));
    }

    void Crosshair::draw(std::unordered_map<ShaderProgram, Shader>& shaders)
    {
        mTexture.bind();
        shaders[CrosshairProgram].use();
        mVertexArray.bind();
        mIndexBuffer.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}
