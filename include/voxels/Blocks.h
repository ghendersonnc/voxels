#pragma once

#include <vector>

#include "Block.h"
#include "enums.h"

namespace Voxels::Blocks
{
    const std::vector blocks{
        Block(0,0,0,0, Air),
        Block(0, 1, 0, 1, Dirt),
        Block(
            1, 2, 1, 2,
            0, 1, 0, 1,
            1, 2, 0, 1, Grass
        ),
        Block(0, 1, 1, 2, Stone),
        Block(0, 1, 1, 2, Wood),
        Block(4, 5, 0, 1, Sand),
    };
}