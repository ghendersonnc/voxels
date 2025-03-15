#include "Vertex.h"

namespace Voxels
{
    
    Vertex::Vertex(int8_t _x, int8_t _y, int8_t _z, uint8_t _tx, uint8_t _ty, float r, float g, float b)
    {
        vertexPosition[0] = _x;
        vertexPosition[1] = _y;
        vertexPosition[2] = _z;
        texturePosition[0] = _tx;
        texturePosition[1] = _ty;
        colorValue[0] = r;
        colorValue[1] = g;
        colorValue[2] = b;
    }
}
