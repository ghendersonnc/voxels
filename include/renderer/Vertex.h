#pragma once
#include <cstdint>

namespace Voxels {
    struct Vertex
    {
        int8_t vertexPosition[3];
        uint8_t texturePosition[2];
        float colorValue[3];

        Vertex(int8_t _x, int8_t _y, int8_t _z, uint8_t _tx, uint8_t _ty, float r = 1.f, float g = 1.f, float b = 1.f);
        
    };
}
