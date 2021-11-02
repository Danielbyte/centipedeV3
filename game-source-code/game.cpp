#include "game.h"
#include <iostream>
#include "game.h"

void Game::run_game()
{
    auto game_ptr = std::make_unique<ScreenManager>();
    game_ptr -> run();
}
