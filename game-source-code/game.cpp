#include "game.h"
#include <iostream>
#include "game.h"

void Game::run_game()
{
    auto game_ptr = std::make_unique<ScreenManager>();
    game_ptr -> run();
}
//Initialize game object
/*Game::Game():
    background(),
    background_texture(),
    playerID(),
    player_texture(),
    screen {VideoMode(gameWidth, gameHeight), "centipede++"}
    {
        if (!font.loadFromFile("resources/sansation.ttf")) throw CouldNotLoadFont{};
        displaySplashScreen();

        if (!background_texture.loadFromFile("resources/background.png")) throw CouldNotLoadPicture{};
        background.setTexture(background_texture);

        if(!player_texture.loadFromFile("resources/player.png")) throw CouldNotLoadPicture{};
        playerID.setTexture(player_texture);
        playerID.setPosition(player_controller.getPlayerInfo().position.x,player_controller.getPlayerInfo().position.y);
        playerID.setOrigin(player_controller.getObject_box().center.x,player_controller.getObject_box().center.y);
    }

void Game::displaySplashScreen()
{
    screen_message.setFont(font);
    screen_message.setCharacterSize(30);
    screen_message.setPosition(70.f, 200.f);
    screen_message.setColor(Color::Red);
    screen_message.setString("welcome to Centipede++"
                             "\nPress Enter key to start!"
                             "\nUse keyboard keys up, down, left and right \nto control player!"
                             "\nPress escape(Esc) to exit game!");

}

void Game::run()
{
    while(screen.isOpen())
    {
        Event event;

        while(screen.pollEvent(event))
        {
            //if window is manually closed or Esc key is pressed
            if ((event.type == Event::Closed) || ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)))
            {
                screen.close();
                break;
            }
            else
            {
                if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Enter))
                    isPlaying = true;
                    //update movement of player object with respect to user input
                    player_controller.process_event(event);
            }
        }
        update_screen(player_controller);
        render_screen();
    }

}

void Game::render_screen()
{
    if (isPlaying)
    {
        screen.draw(background);
        screen.draw(playerID);
    }
    else
        screen.draw(screen_message);

    screen.display();
    screen.clear();
}

void Game::update_screen(Controller& playerController)
{
    playerID.setPosition(playerController.getPlayerInfo().position.x, playerController.getPlayerInfo().position.y);
}*/
