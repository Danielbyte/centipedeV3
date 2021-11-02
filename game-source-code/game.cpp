#include "game.h"
#include <iostream>
#include "game.h"

void Game::run_game()
{
    auto game_ptr = std::make_unique<ScreenManager>();
    //int attempts = 2;
    //while((attempts > 0) && (!game_ptr -> quit_game))
    //{
         game_ptr -> run();
      //   if(game_ptr -> restart_game)
         //{
        //     game_ptr.reset(new ScreenManager);
          //   --attempts;
         //}
    //}

}
