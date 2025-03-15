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
        CrosshairProgram = 1,
    };

    enum BlockType : uint8_t
    {
        Air = 0,
        Dirt = 1,
        Grass = 2,
        Stone = 3,
        Wood = 4,
        Sand = 5,
    };
}