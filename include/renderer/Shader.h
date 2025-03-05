#pragma once
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "enums.h"
#include "Shader.h"

namespace Voxels
{
    

    class Shader
    {
    public:


        Shader(std::string vertexShaderPath, std::string fragmentShaderPath);

        void recompile();
        void use() const;
        void destroy() const;

        void setUniform4f(const std::string& name, glm::vec4 vec) const;
        void setUniform4i(const std::string& name, glm::ivec4 vec) const;

        void setUniformMat4f(const std::string& name, glm::mat4 mat) const;
    private:
        unsigned int mShaderId;
        std::unordered_map<ShaderType, std::string> mShaderPaths;

        void _compileErrors(const unsigned int& shader);
    };
}
