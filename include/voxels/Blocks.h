#pragma once

#include <vector>

#include "Block.h"

namespace Voxels::Blocks
{
    const std::vector<Voxels::Block> blocks{
        Voxels::Block(0,0,0,0),
        Voxels::Block(0, 1, 0, 1),
        Voxels::Block(
            1, 2, 1, 2,
            0, 1, 0, 1,
            1, 2, 0, 1
        ),
        Voxels::Block(0, 1, 1, 2),
        Voxels::Block(0, 1, 1, 2),
        Voxels::Block(4, 5, 0, 1),
    };
}