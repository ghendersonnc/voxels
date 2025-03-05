#pragma once
namespace Voxels {
    struct Vertex
    {
        char vertexPosition[3];
        char texturePosition[2];

        Vertex(char _x, char _y, char _z, char _tx, char _ty);
        
    };
}