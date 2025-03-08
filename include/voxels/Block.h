#pragma once
#include <cstdint>
namespace Voxels
{
    struct Block {
        int8_t topStartX, topEndX, topStartY, topEndY;
        int8_t bottomStartX, bottomEndX, bottomStartY, bottomEndY;
        int8_t sideStartX, sideEndX, sideStartY, sideEndY;

        // For blocks that contain the same texture for all 6 sides
        Block(int8_t startX, int8_t endX, int8_t startY, int8_t endY);
        
        Block(
            int8_t TopStartX, int8_t TopEndX, int8_t TopStartY, int8_t TopEndY,
            int8_t BottomStartX, int8_t BottomEndX, int8_t BottomStartY, int8_t BottomEndY,
            int8_t SideStartX, int8_t SideEndX, int8_t SideStartY, int8_t SideEndY
        );
     };
}