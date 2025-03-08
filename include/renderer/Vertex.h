#pragma once
#include <cstdint>

namespace Voxels {
    struct Vertex
    {
        int8_t vertexPosition[3];
        char texturePosition[2];

        Vertex(int8_t _x, int8_t _y, int8_t _z, int8_t _tx, int8_t _ty);
        
    };
}
