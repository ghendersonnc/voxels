#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Game.h"

int main()
{
    auto logger = spdlog::stdout_color_mt("logger");
    set_default_logger(logger);

    Voxels::Game game;

    if (!game.init())
        return -1;

    game.run();
}