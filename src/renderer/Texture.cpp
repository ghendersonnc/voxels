#include "Texture.h"

#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>

namespace Voxels
{
    Texture::Texture(const std::string& texturePath, const bool flipVertically)
    {
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        stbi_set_flip_vertically_on_load(flipVertically);
        
        int texWidth, texHeight, nrChannels;
        unsigned char* data = stbi_load(texturePath.data(), &texWidth, &texHeight, &nrChannels, 4);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        stbi_image_free(data);
    }

    void Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, mTextureId);
    }

}
