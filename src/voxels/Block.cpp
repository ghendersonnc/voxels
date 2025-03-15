#include "Block.h"

namespace Voxels
{
    Block::Block(int8_t startX, int8_t endX, int8_t startY, int8_t endY, int8_t blockType_)
    {
        topStartX = startX;
        topEndX = endX;
        topStartY = startY;
        topEndY = endY;

        bottomStartX = startX;
        bottomEndX = endX;
        bottomStartY = startY;
        bottomEndY = endY;

        sideStartX = startX;
        sideEndX = endX;
        sideStartY = startY;
        sideEndY = endY;

        blockType = blockType_;
        
    }

    Block::Block(int8_t TopStartX, int8_t TopEndX, int8_t TopStartY, int8_t TopEndY, int8_t BottomStartX,
        int8_t BottomEndX, int8_t BottomStartY, int8_t BottomEndY, int8_t SideStartX, int8_t SideEndX,
        int8_t SideStartY, int8_t SideEndY, int8_t blockType_)
    {
        topStartX = TopStartX;
        topEndX = TopEndX;
        topStartY = TopStartY;
        topEndY = TopEndY;

        bottomStartX = BottomStartX;
        bottomEndX = BottomEndX;
        bottomStartY = BottomStartY;
        bottomEndY = BottomEndY;

        sideStartX = SideStartX;
        sideEndX = SideEndX;
        sideStartY = SideStartY;
        sideEndY = SideEndY;

        blockType = blockType_;
    }
}
