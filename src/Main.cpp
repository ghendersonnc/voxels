#include "Game.h"


int main()
{
    Voxels::Game game;

    if (!game.init())
        return -1;

    game.run();
}