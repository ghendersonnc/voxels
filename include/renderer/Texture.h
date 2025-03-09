#pragma once
#include <string>

namespace Voxels
{
    class Texture {
    public:
        Texture(const std::string& texturePath, const bool flipVertically);
        void bind();

    private:
        unsigned int mTextureId;
    };
}
