#include "Crosshair.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "Definitions.h"


namespace Voxels
{
    Crosshair::Crosshair()
    {
        using namespace Definitions;

        float aspect = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);
        float x = 0.01f;
        float y = x * aspect;
        std::vector vertices{
            x, y, // top right
            x, -y, // bottom right
            -x, -y, // bottom left
            -x, y, // top left 
        };

        std::vector indices{
            0, 1, 3, // first triangle
            1, 2, 3 // second triangle
        };
        mVertexArray.bind();
        mVertexBuffer.setData(vertices, sizeof(float) * vertices.size());
        mIndexBuffer.setData(indices, sizeof(int) * indices.size());
        mVertexArray.linkAttributes(mVertexBuffer, 0, 2, GL_FLOAT, 2 * sizeof(float), nullptr);
    }

    void Crosshair::draw(std::unordered_map<ShaderProgram, Shader>& shaders)
    {
        shaders[CrosshairProgram].use();
        mVertexArray.bind();
        mIndexBuffer.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}
