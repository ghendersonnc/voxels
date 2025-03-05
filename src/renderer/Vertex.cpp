#include "Vertex.h"

namespace Voxels
{
    
    Vertex::Vertex(char _x, char _y, char _z, char _tx, char _ty)
    {
        vertexPosition[0] = _x;
        vertexPosition[1] = _y;
        vertexPosition[2] = _z;
        texturePosition[0] = _tx;
        texturePosition[1] = _ty;
    }
}
