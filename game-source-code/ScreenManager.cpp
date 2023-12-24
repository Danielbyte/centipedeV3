#include "ScreenManager.h"
ScreenManager::ScreenManager():

    quit_game{false},
    restart_game{false},
    reset_high_score{false},
    bodiesToSpawn{11}, //spawn 11 body segments
    isPlaying{false},
    window(sf::VideoMode(windowWidth, windowHeight), "CENTIPEDE++"),
    shoot_timer{2},
    isGameOver{false}

{
    initialize_screen();
    initialize_player();
    create_enemy();
    logic.create_mushrooms(mushField, mushroom_sprites);
}

void ScreenManager::initialize_player()
{
    if(!playerSprite_texture.loadFromFile("resources/player.png")) throw CouldNotLoadPicture{};
    player_sprite.setTexture(playerSprite_texture);
    player_sprite.setPosition(logic.player_object.get_Xposition(), logic.player_object.get_Yposition());
    player_sprite.setOrigin(sf::Vector2f(player_size/2, player_size/2));
}

void ScreenManager::initialize_screen()
{
    Displays.loadFromFile("resources/sansation.ttf");
    splash_screenFont.loadFromFile("resources/sansation.ttf");
    splash_screenDisplay.setFont(splash_screenFont);
    splash_screenDisplay.setCharacterSize(20);
    splash_screenDisplay.setStyle(sf::Text::Regular);
    splash_screenDisplay.setFillColor(sf::Color::Red);
    splash_screenDisplay.setPosition(10,180);
    splash_screenDisplay.setString("Welcome to Centipede++");

    //game instructions set up
    game_instructions.setFont(splash_screenFont);
    game_instructions.setCharacterSize(20);
    game_instructions.setStyle(sf::Text::Regular);
    game_instructions.setFillColor(sf::Color::Red);
    game_instructions.setPosition(10, 220);
    game_instructions.setString("INSTRUCTIONS: \nPress Enter to start game!"
                                "\nPress Escape(Esc) to quit!"
                                "\nUse keyboard arrows to move player"
                                "\nPress space to shoot");

    playerLives_display.setFont(Displays);
    playerLives_display.setCharacterSize(12);
    playerLives_display.setStyle(sf::Text::Bold);
    playerLives_display.setFillColor(sf::Color::Red);
    playerLives_display.setPosition(0,0);

    currentScore_display.setFont(Displays);
    currentScore_display.setCharacterSize(12);
    currentScore_display.setStyle(sf::Text::Bold);
    currentScore_display.setFillColor(sf::Color::Red);
    currentScore_display.setPosition(70, 0);

    highScore_display.setFont(Displays);
    highScore_display.setCharacterSize(12);
    highScore_display.setStyle(sf::Text::Bold);
    highScore_display.setFillColor(sf::Color::Green);
    highScore_display.setPosition(300, 0);

}

void ScreenManager::run()
{
    //uniform game speed
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    while(window.isOpen())
    {
        process_events();
        if(isPlaying)
        {
            //needs to update screen accordingly
            update();
            //draw game entities
            draw_game_entities();
        }

        else
        {
            window.draw(splash_screenDisplay);
            if (!isGameOver)
            {
                window.draw(game_instructions);
            }
        }

        window.display();
        window.clear();
    }
}

void ScreenManager::draw_game_entities()
{
    draw_mushrooms();
    window.draw(player_sprite);
   
    for (auto& centipede_segment : CentipedeSprite_vector) // draw centipede (only the head for now)
    {
        window.draw(*centipede_segment);
    }

    for (auto& bullet : bulletSprites_vector) // draw bullets on screen
    {
        //(bullet) ->Draw(_window);
        window.draw(*bullet);
    }
    //draw scorpion
    for (auto& scorpion_ : scorpion_sprite_vector)
    {
        window.draw(*scorpion_);
    }

    //output spider
    for (auto& spider : spider_sprite_vector)
    {
        window.draw(*spider);
    }

    //draw bombs
    for(auto& bomb : DDTBombs_spiteVector)
    {
        window.draw(*bomb);
    }

    //draw flea
    for(auto& flea : FleaSprite_vector)
    {
        window.draw(*flea);
    }
}

void ScreenManager::process_events()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape)
            {
                quit_game = true;
                window.close();
            }

            else if ((event.key.code == sf::Keyboard::RShift && isGameOver) || (event.key.code == sf::Keyboard::LShift && isGameOver))
            {
                restart_game = true;
                window.close();
            }

            else if(event.key.code == sf::Keyboard::R && isGameOver)
            {
                reset_high_score = true;
                //window.close();
            }

            else
                keyboard_handling(event.key.code, true);
            break;

        case sf::Event::KeyReleased:
            keyboard_handling(event.key.code, false);
            break;

        case sf::Event::Closed:
            quit_game = true;
            window.close();
            break;

        default:
            ;

        }
    }
}

void ScreenManager::keyboard_handling(sf::Keyboard::Key key, bool isPressed)
{


    if (shoot_timer < 2)
    {
        shoot_timer++;
    }

    if(key == sf::Keyboard::Enter) //player wants to play
        isPlaying = true;
    if(isPlaying)
    {
        window.setKeyRepeatEnabled(true);
        if(key == sf::Keyboard::Up)
        {
            logic.player_object.setPlayer_movement(Direction::Up, isPressed, player_sprite);
        }
        else if(key == sf::Keyboard::Down)
        {
            //player should move down
            logic.player_object.setPlayer_movement(Direction::Down, isPressed, player_sprite);
        }
        else if(key == sf::Keyboard::Right)
        {
            //player should move right
            logic.player_object.setPlayer_movement(Direction::Right, isPressed, player_sprite);
        }
        else if(key == sf::Keyboard::Left)
        {
            //player should move down
            logic.player_object.setPlayer_movement(Direction::Left, isPressed,player_sprite);
        }
        else if (key == sf::Keyboard::Space && shoot_timer >= 2)
        {
            window.setKeyRepeatEnabled(false);
            sound_manager->playLaserSound();
            create_laserShots();
            shoot_timer = 0;
        }
    }
}

void ScreenManager::update()
{
    //Query logic to update game entities
    update_game_entities();
    //scorpion updates
    auto canSpawnScorpion = logic.canSpawn_scorpion();

    if (canSpawnScorpion)
    {
        create_scorpion();
    }

    //spider updates
    auto canSpawnSpider = logic.getIfCanSpawnSpider();
    if(canSpawnSpider && (spider_sprite_vector.empty()))
    {
        //time to create a spider!
        create_spider();
    }

    //query logic if can spawn bomb
    auto canSpawnBomb = logic.getIfCanSpawnBomb();
    if(canSpawnBomb)
    {
        //request logic to create bomb
        create_bomb();
    }

    //query logic to spawn flea
    auto canSpawnFlea = logic.getIfCanSpawnFlea(mushField);
    if(canSpawnFlea && (FleaSprite_vector.empty()))
    {
        //std::cout << "need to spawn flea!" << std::endl;
        create_flea();
    }

    if(!FleaSprite_vector.empty())
    {
        //ask the logic to update flea
        logic.update_flea(FleaSprite_vector,mushField, mushroom_sprites);
    }


    updateScreen_manager();
    update_game();

}

void ScreenManager::update_game_entities()
{
    
    logic.update_player(player_sprite);
    logic.updateLaserShots(bulletSprites_vector);
    logic.update_centipede(CentipedeSprite_vector,mushField);
    //logic.collisionBetween_mushAndPlayer(player_sprite);
    logic.collisionBetweenBulletsAndObjects(bulletSprites_vector, CentipedeSprite_vector,mushField, mushroom_sprites);
    logic.collision_between_mush_and_spider(false,mushField, mushroom_sprites);

    logic.collision_between_player_and_spider(player_sprite);
    logic.collision_btwn_bullet_and_spider(bulletSprites_vector, spider_sprite_vector);
    logic.collision_between_bullet_and_bomb(bulletSprites_vector, DDTBombs_spiteVector, spider_sprite_vector,
                                            CentipedeSprite_vector, scorpion_sprite_vector, player_sprite,
                                            FleaSprite_vector,mushField, mushroom_sprites);

    logic.collision_between_bullet_and_flea(bulletSprites_vector, FleaSprite_vector);
    logic.collision_between_player_and_flea(player_sprite);
    logic.collision_between_centipede_and_player(player_sprite);
    logic.collision_between_bullet_and_scorpion(bulletSprites_vector,scorpion_sprite_vector);
    logic.collision_between_centipede_and_bullet(bulletSprites_vector, CentipedeSprite_vector,mushField, mushroom_sprites);
    logic.update_spider(spider_sprite_vector);
    logic.update_scorpion(scorpion_sprite_vector,mushField, mushroom_sprites);
}

void ScreenManager::create_laserShots()
{
    logic.create_bullet(bulletSprites_vector);
}

void ScreenManager::create_enemy()
{
    //create enemy object via logic layer
    logic.create_centipede(true, bodiesToSpawn, CentipedeSprite_vector);
}

void ScreenManager::create_scorpion()
{
    sf::Vector2f pos_ = logic.create_scorpion();
    auto scorpion_sprite = std::make_shared<sf::Sprite>(sf::Sprite());
    if(!scorpion_texture.loadFromFile("resources/scorpion1.png")) throw CouldNotLoadPicture{};
    scorpion_sprite -> setOrigin(sf::Vector2f(0.f, 0.f));
    scorpion_sprite -> setTexture(scorpion_texture);
    scorpion_sprite -> setPosition(pos_);
    scorpion_sprite_vector.push_back(scorpion_sprite);
}

void ScreenManager::create_spider()
{
    sf::Vector2f pos_ = logic.create_spider();
    auto spider_sprite = std::make_shared<sf::Sprite>(sf::Sprite());
    if(!spider_texture.loadFromFile("resources/spider1.png")) throw CouldNotLoadPicture{};
    spider_sprite -> setOrigin(sf::Vector2f(0.f,0.f));
    spider_sprite -> setTexture(spider_texture);
    spider_sprite -> setPosition(pos_);
    spider_sprite_vector.push_back(spider_sprite);
}

void ScreenManager::create_bomb()
{
    sf::Vector2f pos = logic.create_bomb();
    auto bomb_sprite = std::make_shared<sf::Sprite>(sf::Sprite());
    if(!bomb_texture.loadFromFile("resources/bomb1.png")) throw CouldNotLoadPicture{};
    bomb_sprite ->setTexture(bomb_texture);
    bomb_sprite -> setOrigin(sf::Vector2f(8.f, 8.f));
    bomb_sprite -> setPosition(pos);
    DDTBombs_spiteVector.push_back(bomb_sprite);
}

void ScreenManager::draw_mushrooms()
{
  
    for (auto& mushroom_sprite : mushroom_sprites)
    {
       window.draw(*mushroom_sprite);
    }
}

void ScreenManager::updateScreen_manager()
{
    auto remainingPlayer_lives = logic.player_object.getPlayer_lives();
    std::string remainingPlayer_lives_ = std::to_string(remainingPlayer_lives);
    playerLives_display.setString("LIVES: " + remainingPlayer_lives_);
    window.draw(playerLives_display);

    //Display current score
    auto current_score = logic.get_score();
    std::string _currentScore = std::to_string(current_score);
    currentScore_display.setString("SCORE: " + _currentScore);
    window.draw(currentScore_display);

    //Display and save high score
    auto high_score = score_manager.highScoreDisplay(current_score);
    std::string highScore = std::to_string(high_score);
    highScore_display.setString("HIGH SCORE: " + highScore);
    window.draw(highScore_display);

}

void ScreenManager::update_game()
{
    splash_screenDisplay.setPosition(125, 208);
    splash_screenDisplay.setCharacterSize(20);

    // Game should terminate if player lives = zero
    // see if player is still alive
    auto player_status = logic.player_object.getPlayer_state();
    if(!player_status)
    {
        isPlaying = false;
        isGameOver = true;
        window.clear();
        splash_screenDisplay.setString("YOU LOST!"
                                       "\nGAME OVER"
                                       "\nPress Escape(Esc) key to quit"
                                       "\nPress R to reset highscore");
    }

    //if all centipede segments are killed, player wins
    if(CentipedeSprite_vector.empty())
    {
        isPlaying = false;
        isGameOver = true;
        window.clear();
        splash_screenDisplay.setFillColor(sf::Color::Green);
        splash_screenDisplay.setString("YOU WIN!"
                                       "\nGAME OVER"
                                       "\nPress Escape(Esc) key to quit"
                                       "\nPress R to reset highscore");
    }
}

void ScreenManager::create_flea()
{
    auto flea_sprite = std::make_shared<sf::Sprite>(sf::Sprite());
    auto pos = logic.create_flea();
    if(!flea_texture.loadFromFile("resources/flea1.png")) throw CouldNotLoadPicture{};
    flea_sprite ->setTexture(flea_texture);
    flea_sprite -> setOrigin(sf::Vector2f(0.f,0.f));
    flea_sprite -> setPosition(pos);
    FleaSprite_vector.push_back(flea_sprite);
}

//Free up resources
ScreenManager::~ScreenManager()
{
    bulletSprites_vector.clear();
    CentipedeSprite_vector.clear();
    DDTBombs_spiteVector.clear();
    FleaSprite_vector.clear();
    scorpion_sprite_vector.clear();
    spider_sprite_vector.clear();
    mushField.clear();
}

