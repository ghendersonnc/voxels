#pragma once

namespace Voxels
{
    enum ShaderType : uint8_t {
        VertexShader = 1 << 0,
        FragmentShader = 1 << 1,
    };

    enum ShaderProgram : uint8_t
    {
        ChunkProgram = 0,
    };
}