#include "ScreenManager.h"
ScreenManager::ScreenManager():

    quit_game{false},
    restart_game{false},
    reset_high_score{false},
    bodiesToSpawn{11}, //spawn 11 body segments
    isPlaying{false},
    window(sf::VideoMode(windowWidth, windowHeight), "CENTIPEDE++"),
    shoot_timer{2},
    isGameOver{false},
    playerBombed{false},
    inMainMenu{true},
    viewingInstructions{false},
    animation_period{0.1f},
    instructions_offset{60.0f},
    inEndMenu{false},
    totalCentipedeSegments{12}

{
    cursorStartGamePos.y = 214.8f;
    cursorStartGamePos.x = 105.0f;

    cursorInstructionsPos.x = 155.0f;
    cursorInstructionsPos.y = 244.8f;

    cursorQuitGamePos.x = 255.0f;
    cursorQuitGamePos.y = 274.8f;

    if (!scorpion_texture.loadFromFile("resources/scorpion1.png")) throw CouldNotLoadPicture{};
    if (!bomb_texture.loadFromFile("resources/bomb1.png")) throw CouldNotLoadPicture{};
    if (!flea_texture.loadFromFile("resources/flea1.png")) throw CouldNotLoadPicture{};
    if (!spider_texture.loadFromFile("resources/spider1.png")) throw CouldNotLoadPicture{};
    if (!life1_t.loadFromFile("resources/1-life.png")) throw CouldNotLoadPicture{};
    if (!lives2_t.loadFromFile("resources/2-lives.png")) throw CouldNotLoadPicture{};
    if (!lives3_t.loadFromFile("resources/3-lives.png")) throw CouldNotLoadPicture{};
    if (!menu_cursor_t.loadFromFile("resources/game-cursor.png")) throw CouldNotLoadPicture{};
    if (!instructions_background_t.loadFromFile("resources/instructions-background.png")) throw CouldNotLoadPicture{};
    if (!bulletPoint1_t.loadFromFile("resources/bulletPoint1.png")) throw CouldNotLoadPicture{};
    if (!bulletPoint2_t.loadFromFile("resources/bulletPoint2.png")) throw CouldNotLoadPicture{};
    load_resources();

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
    Displays.loadFromFile("resources/ARCADE_N.ttf");
    splash_screenFont.loadFromFile("resources/ARCADE_N.ttf");
    splash_screenDisplay.setFont(splash_screenFont);
    splash_screenDisplay.setCharacterSize(12);
    splash_screenDisplay.setStyle(sf::Text::Regular);
    splash_screenDisplay.setFillColor(sf::Color::Red);
    splash_screenDisplay.setPosition(10,180);

    main_menu_t.loadFromFile("resources/main-menu.png");
    main_menu_s.setOrigin(windowWidth / 2.0f, windowHeight / 2.0f);
    main_menu_s.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);
    main_menu_s.setTexture(main_menu_t);

    instructions_background_s.setOrigin(windowWidth / 2.0f, windowHeight / 2.0f);
    instructions_background_s.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);
    instructions_background_s.setTexture(instructions_background_t);

    //MAIN MENU TEXTS
    //Start game text setup
    start_Game_txt.setFont(splash_screenFont);
    start_Game_txt.setCharacterSize(12);
    start_Game_txt.setStyle(sf::Text::Regular);
    start_Game_txt.setFillColor(sf::Color::Green);
    start_Game_txt.setPosition(120, 215);
    start_Game_txt.setString("START GAME");

    //game instructions text set up
    game_instructions_txt.setFont(splash_screenFont);
    game_instructions_txt.setCharacterSize(12);
    game_instructions_txt.setStyle(sf::Text::Regular);
    game_instructions_txt.setFillColor(sf::Color::Red);
    game_instructions_txt.setPosition(170, 245);
    game_instructions_txt.setString("INSTRUCTIONS");

    //quit game text set up
    quit_Game_txt.setFont(splash_screenFont);
    quit_Game_txt.setCharacterSize(12);
    quit_Game_txt.setStyle(sf::Text::Regular);
    quit_Game_txt.setFillColor(sf::Color::Red);
    quit_Game_txt.setPosition(270, 275);
    quit_Game_txt.setString("QUIT GAME");

    menu_cursor_s.setOrigin(0.0f, 0.0f);
    menu_cursor_s.setPosition(105.0f, 214.8f);
    menu_cursor_s.setTexture(menu_cursor_t);

    //Player lives heads up display
    player_livesHUD_s.setPosition(0.0f, 0.0f);
    player_livesHUD_s.setTexture(lives3_t);

    currentScore_display.setFont(Displays);
    currentScore_display.setCharacterSize(8);
    currentScore_display.setStyle(sf::Text::Regular);
    currentScore_display.setFillColor(sf::Color::Red);
    currentScore_display.setPosition(70, 0);

    highScore_display.setFont(Displays);
    highScore_display.setCharacterSize(8);
    highScore_display.setStyle(sf::Text::Regular);
    highScore_display.setFillColor(sf::Color::Green);
    highScore_display.setPosition(300, 0);

    game_instruction1_txt.setFont(splash_screenFont);
    game_instruction1_txt.setCharacterSize(10);
    game_instruction1_txt.setStyle(sf::Text::Regular);
    game_instruction1_txt.setFillColor(sf::Color::Green);
    game_instruction1_txt.setPosition(15.0f, 80.0f + instructions_offset);
    game_instruction1_txt.setString("Use arrow keys to move player.");

    instruction1_bulletPoint_s.setTexture(bulletPoint1_t);
    instruction1_bulletPoint_s.setPosition(0.0f, 80.0f + instructions_offset);

    game_instruction2_txt.setFont(splash_screenFont);
    game_instruction2_txt.setCharacterSize(10);
    game_instruction2_txt.setStyle(sf::Text::Regular);
    game_instruction2_txt.setFillColor(sf::Color::Green);
    game_instruction2_txt.setPosition(15.0f, 100.0f + instructions_offset);
    game_instruction2_txt.setString("Press Space to shoot.");

    instruction2_bulletPoint_s.setTexture(bulletPoint1_t);
    instruction2_bulletPoint_s.setPosition(0.0f, 100.0f + instructions_offset);

    game_instruction3_txt.setFont(splash_screenFont);
    game_instruction3_txt.setCharacterSize(10);
    game_instruction3_txt.setStyle(sf::Text::Regular);
    game_instruction3_txt.setFillColor(sf::Color::Green);
    game_instruction3_txt.setPosition(15.0f, 120.0f + instructions_offset);
    game_instruction3_txt.setString("Game ends when player depletes all 3 lives"
                                    "\nor when all centipede segments are shot.");

    instruction3_bulletPoint_s.setTexture(bulletPoint1_t);
    instruction3_bulletPoint_s.setPosition(0.0f, 120.0f + instructions_offset);

    game_instruction4_txt.setFont(splash_screenFont);
    game_instruction4_txt.setCharacterSize(10);
    game_instruction4_txt.setStyle(sf::Text::Regular);
    game_instruction4_txt.setFillColor(sf::Color::Green);
    game_instruction4_txt.setPosition(15.0f, 155.0f + instructions_offset);
    game_instruction4_txt.setString("Press ESC key to escape from game window.");

    instruction4_bulletPoint_s.setTexture(bulletPoint1_t);
    instruction4_bulletPoint_s.setPosition(0.0f, 155.0f + instructions_offset);

    game_instruction5_txt.setFont(splash_screenFont);
    game_instruction5_txt.setCharacterSize(10);
    game_instruction5_txt.setStyle(sf::Text::Regular);
    game_instruction5_txt.setFillColor(sf::Color::Green);
    game_instruction5_txt.setPosition(15.0f, 190.0f + instructions_offset);
    game_instruction5_txt.setString("ENEMIES:");

    instruction5_bulletPoint_s.setTexture(bulletPoint1_t);
    instruction5_bulletPoint_s.setPosition(0.0f, 190.0f + instructions_offset);

    scorpion_enemy_s.setTexture(scorpion1_enemy_t);
    scorpion_enemy_s.setPosition(0.0f, 210.0f + instructions_offset);

    scorpion_instructions_txt.setFont(splash_screenFont);
    scorpion_instructions_txt.setCharacterSize(10);
    scorpion_instructions_txt.setStyle(sf::Text::Regular);
    scorpion_instructions_txt.setFillColor(sf::Color::Green);
    scorpion_instructions_txt.setPosition(25.0f, 210.0f + instructions_offset);
    scorpion_instructions_txt.setString("Poisons every mushroom it touches.");

    spider_enemy_s.setTexture(scorpion1_enemy_t);
    spider_enemy_s.setPosition(0.0f, 230.0f + instructions_offset);

    spider_instructions_txt.setFont(splash_screenFont);
    spider_instructions_txt.setCharacterSize(10);
    spider_instructions_txt.setStyle(sf::Text::Regular);
    spider_instructions_txt.setFillColor(sf::Color::Green);
    spider_instructions_txt.setPosition(23.0f, 230.0f + instructions_offset);
    spider_instructions_txt.setString("Eats some mushrooms around player area.");

    segment_enemy_s.setTexture(segment1_enemy_t);
    segment_enemy_s.setPosition(0.0f, 250.0f + instructions_offset);

    centipede_instructions_txt.setFont(splash_screenFont);
    centipede_instructions_txt.setCharacterSize(10);
    centipede_instructions_txt.setStyle(sf::Text::Regular);
    centipede_instructions_txt.setFillColor(sf::Color::Green);
    centipede_instructions_txt.setPosition(15.0f, 250.0f + instructions_offset);
    centipede_instructions_txt.setString("Gets infected by poisoned mushroom and"
        "\nkills player on collision.");

    flea_enemy_s.setTexture(flea1_enemy_t);
    flea_enemy_s.setPosition(-8.5f, 285.0f + instructions_offset);

    flea_instructions_txt.setFont(splash_screenFont);
    flea_instructions_txt.setCharacterSize(10);
    flea_instructions_txt.setStyle(sf::Text::Regular);
    flea_instructions_txt.setFillColor(sf::Color::Green);
    flea_instructions_txt.setPosition(16.5f, 285.0f + instructions_offset);
    flea_instructions_txt.setString("Leaves a trail of mushrooms behind");

    backToMainMenu_txt.setFont(splash_screenFont);
    backToMainMenu_txt.setCharacterSize(10);
    backToMainMenu_txt.setStyle(sf::Text::Regular);
    backToMainMenu_txt.setFillColor(sf::Color::Red);
    backToMainMenu_txt.setPosition(245.0f, 400.0f);
    backToMainMenu_txt.setString("Main menu (PRESS Enter)");

    playerScoreTag.setFont(splash_screenFont);
    playerScoreTag.setCharacterSize(12);
    playerScoreTag.setStyle(sf::Text::Bold);
    playerScoreTag.setFillColor(sf::Color::Green);
    playerScoreTag.setString("YOUR SCORE");

    playerScore.setFont(splash_screenFont);
    playerScore.setCharacterSize(12);
    playerScore.setStyle(sf::Text::Bold);
    playerScore.setFillColor(sf::Color::Green);

    highestScoreTag.setFont(splash_screenFont);
    highestScoreTag.setCharacterSize(12);
    highestScoreTag.setStyle(sf::Text::Bold);
    highestScoreTag.setFillColor(sf::Color::Green);
    highestScoreTag.setString("HIGH SCORE");

    highestScore.setFont(splash_screenFont);
    highestScore.setCharacterSize(12);
    highestScore.setStyle(sf::Text::Bold);
    highestScore.setFillColor(sf::Color::Green);

    resetHighScore_txt.setFont(splash_screenFont);
    resetHighScore_txt.setCharacterSize(12);
    resetHighScore_txt.setStyle(sf::Text::Regular);
    resetHighScore_txt.setFillColor(sf::Color::Green);
    resetHighScore_txt.setString("reset high score");

    endGameQuit_txt.setFont(splash_screenFont);
    endGameQuit_txt.setCharacterSize(12);
    endGameQuit_txt.setStyle(sf::Text::Regular);
    endGameQuit_txt.setFillColor(sf::Color::Green);
    endGameQuit_txt.setString("Quit game");
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
            //play background sound
            sound_manager->playBackGroundSound();
            //needs to update screen accordingly
            update();
            //draw game entities
            draw_game_entities();
        }

        else
        {
            if (inMainMenu && !viewingInstructions)
            {
                window.draw(main_menu_s);
                window.draw(menu_cursor_s);
                window.draw(start_Game_txt);
                window.draw(game_instructions_txt);
                window.draw(quit_Game_txt);
            }

            if (inMainMenu && viewingInstructions)
                displayGameInstructions();

            if (inEndMenu)
                displayWinningMenu();
            
        }

        window.display();
        window.clear();
    }
}

void ScreenManager::draw_game_entities()
{
    draw_mushrooms();
    logic.updatePlayerTexture(player_sprite);
    window.draw(player_sprite);
   
    for (auto& centipede_segment : CentipedeSprite_vector) // draw centipede (only the head for now)
    {
        window.draw(*centipede_segment);
    }

    if (!shot_centipede_segment_sprites.empty())
    {
        for (auto& shot_segment : shot_centipede_segment_sprites)
        {
            window.draw(*shot_segment);
        }
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
    if ((inMainMenu || inEndMenu) && isPressed)
    {
        switch (key)
        {
        case sf::Keyboard::Up:
                moveCursorUp();
            break;
        case sf::Keyboard::Down:
                moveCursorDown();
            break;
        case sf::Keyboard::Enter:
                processCursorEvents();
            break;
        default:
            break;
        }
    }

    if(isPlaying)
    {
        window.setKeyRepeatEnabled(true);
        auto inDeathAnimation = logic.isInPlayerDeathAnimation();

        if(key == sf::Keyboard::Up)
        {
            logic.player_object.setPlayer_movement(Direction::Up, isPressed, inDeathAnimation, player_sprite);
        }
        else if(key == sf::Keyboard::Down)
        {
            //player should move down
            logic.player_object.setPlayer_movement(Direction::Down, isPressed, inDeathAnimation, player_sprite);
        }
        else if(key == sf::Keyboard::Right)
        {
            //player should move right
            logic.player_object.setPlayer_movement(Direction::Right, isPressed, inDeathAnimation, player_sprite);
        }
        else if(key == sf::Keyboard::Left)
        {
            //player should move down
            logic.player_object.setPlayer_movement(Direction::Left, isPressed, inDeathAnimation, player_sprite);
        }
        else if (key == sf::Keyboard::Space && shoot_timer >= 2)
        {
            if (!inDeathAnimation)
            {
                window.setKeyRepeatEnabled(false);
                sound_manager->playLaserSound();
                create_laserShots();
                shoot_timer = 0;
            }
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
    logic.refresh_game_world(mushField,mushroom_sprites,CentipedeSprite_vector,spider_sprite_vector,scorpion_sprite_vector,
        FleaSprite_vector); //Function executes just after player dies

    logic.update_player(player_sprite);
    logic.updateLaserShots(bulletSprites_vector);
    logic.update_centipede(CentipedeSprite_vector,mushField);
    //logic.collisionBetween_mushAndPlayer(player_sprite);
    logic.collisionBetweenBulletsAndObjects(bulletSprites_vector, CentipedeSprite_vector,mushField, mushroom_sprites);
    logic.collision_between_mush_and_spider(false,mushField, mushroom_sprites);

    logic.collision_between_player_and_spider(player_sprite, spider_sprite_vector);
    logic.collision_btwn_bullet_and_spider(bulletSprites_vector, spider_sprite_vector);
    logic.collision_between_bullet_and_bomb(bulletSprites_vector, DDTBombs_spiteVector, spider_sprite_vector,
                                            CentipedeSprite_vector, scorpion_sprite_vector, player_sprite, playerBombed,
                                            FleaSprite_vector,mushField, mushroom_sprites);

    logic.collision_between_bullet_and_flea(bulletSprites_vector, FleaSprite_vector);
    logic.collision_between_player_and_flea(player_sprite, FleaSprite_vector);
    logic.collision_between_centipede_and_player(player_sprite, CentipedeSprite_vector);
    logic.collision_between_bullet_and_scorpion(bulletSprites_vector,scorpion_sprite_vector);
    logic.collision_between_centipede_and_bullet(bulletSprites_vector, CentipedeSprite_vector,mushField, mushroom_sprites,
        shot_centipede_segment_sprites);
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
    scorpion_sprite -> setOrigin(sf::Vector2f(0.f, 0.f));
    scorpion_sprite -> setTexture(scorpion_texture);
    scorpion_sprite -> setPosition(pos_);
    scorpion_sprite_vector.push_back(scorpion_sprite);
}

void ScreenManager::create_spider()
{
    sf::Vector2f pos_ = logic.create_spider();
    auto spider_sprite = std::make_shared<sf::Sprite>(sf::Sprite());
    spider_sprite -> setOrigin(sf::Vector2f(0.f,0.f));
    spider_sprite -> setTexture(spider_texture);
    spider_sprite -> setPosition(pos_);
    spider_sprite_vector.push_back(spider_sprite);
}

void ScreenManager::create_bomb()
{
    sf::Vector2f pos = logic.create_bomb();
    auto bomb_sprite = std::make_shared<sf::Sprite>(sf::Sprite());
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
    updatePlayerLivesHUD(remainingPlayer_lives);
    window.draw(player_livesHUD_s);

    //Display current score
    auto current_score = logic.get_score();
    std::string _currentScore = std::to_string(current_score);
    currentScore_display.setString("SCORE:" + _currentScore);
    window.draw(currentScore_display);

    //Display and save high score
    auto high_score = score_manager.highScoreDisplay(current_score);
    std::string highScore = std::to_string(high_score);
    highScore_display.setString("HIGH SCORE:" + highScore);
    window.draw(highScore_display);

}

void ScreenManager::update_game()
{
    splash_screenDisplay.setPosition(125, 208);
    splash_screenDisplay.setCharacterSize(12);

    // Game should terminate if player lives = zero
    // see if player is still alive
    auto player_status = logic.player_object.getPlayer_state();
    if(!player_status)
    {
        isPlaying = false;
        isGameOver = true;
        inEndMenu = true;
        menu_cursor_s.setPosition(130.0f, 264.8f);
        resetHighScore_txt.setFillColor(sf::Color::Red);
        window.clear();
    }

    //if all centipede segments are killed, player wins
    auto killed_segments = logic.getNumberOfShotSegments();
    if(killed_segments == totalCentipedeSegments)
    {
        isPlaying = false;
        isGameOver = true;
        inEndMenu = true;
        menu_cursor_s.setPosition(130.0f, 264.8f);
        resetHighScore_txt.setFillColor(sf::Color::Red);
        window.clear();
    }
}

void ScreenManager::create_flea()
{
    auto flea_sprite = std::make_shared<sf::Sprite>(sf::Sprite());
    auto pos = logic.create_flea();
    flea_sprite ->setTexture(flea_texture);
    flea_sprite -> setOrigin(sf::Vector2f(0.f,0.f));
    flea_sprite -> setPosition(pos);
    FleaSprite_vector.push_back(flea_sprite);
}

void ScreenManager::updatePlayerLivesHUD(const int lives)
{
    switch (lives)
    {
    case 1:
        player_livesHUD_s.setTexture(life1_t);
        break;
    case 2:
        player_livesHUD_s.setTexture(lives2_t);
        break;
    default:
        player_livesHUD_s.setTexture(lives3_t);
        break;
    }
}

void ScreenManager::moveCursorDown()
{
    sf::Vector2f cursorPosition = menu_cursor_s.getPosition();
    if (cursorPosition == cursorStartGamePos)
    {
        menu_cursor_s.setPosition(cursorInstructionsPos);
        quit_Game_txt.setFillColor(sf::Color::Red);
        start_Game_txt.setFillColor(sf::Color::Red);
        game_instructions_txt.setFillColor(sf::Color::Green);
    }
    if (cursorPosition == cursorInstructionsPos)
    {
        menu_cursor_s.setPosition(cursorQuitGamePos);
        quit_Game_txt.setFillColor(sf::Color::Green);
        start_Game_txt.setFillColor(sf::Color::Red);
        game_instructions_txt.setFillColor(sf::Color::Red);
    }
    if (cursorPosition == cursorQuitGamePos)
    {
        menu_cursor_s.setPosition(cursorStartGamePos);
        quit_Game_txt.setFillColor(sf::Color::Red);
        start_Game_txt.setFillColor(sf::Color::Green);
        game_instructions_txt.setFillColor(sf::Color::Red);
    }

    if (inEndMenu)
    {
        sf::Vector2f quitEndMenu;
        quitEndMenu.x = 173.0f;
        quitEndMenu.y = 289.8f;

        sf::Vector2f resetHighScrorePos;
        resetHighScrorePos.x = 130.0f;
        resetHighScrorePos.y = 264.8f;

        if (cursorPosition == quitEndMenu)
        {
            menu_cursor_s.setPosition(resetHighScrorePos);
            resetHighScore_txt.setFillColor(sf::Color::Red);
            endGameQuit_txt.setFillColor(sf::Color::Green);
        }

        if (cursorPosition == resetHighScrorePos)
        {
            menu_cursor_s.setPosition(quitEndMenu);
            resetHighScore_txt.setFillColor(sf::Color::Green);
            endGameQuit_txt.setFillColor(sf::Color::Red);
        }
    }
}

void ScreenManager::moveCursorUp()
{
    sf::Vector2f cursorPosition = menu_cursor_s.getPosition();
    if (cursorPosition == cursorStartGamePos)
    {
        menu_cursor_s.setPosition(cursorQuitGamePos);
        quit_Game_txt.setFillColor(sf::Color::Green);
        start_Game_txt.setFillColor(sf::Color::Red);
        game_instructions_txt.setFillColor(sf::Color::Red);
    }
    if (cursorPosition == cursorInstructionsPos)
    {
        menu_cursor_s.setPosition(cursorStartGamePos);
        quit_Game_txt.setFillColor(sf::Color::Red);
        start_Game_txt.setFillColor(sf::Color::Green);
        game_instructions_txt.setFillColor(sf::Color::Red);
    }
    if (cursorPosition == cursorQuitGamePos)
    {
        menu_cursor_s.setPosition(cursorInstructionsPos);
        quit_Game_txt.setFillColor(sf::Color::Red);
        start_Game_txt.setFillColor(sf::Color::Red);
        game_instructions_txt.setFillColor(sf::Color::Green);
    }

    if (inEndMenu)
    {
        sf::Vector2f quitEndMenu;
        quitEndMenu.x = 173.0f;
        quitEndMenu.y = 289.8f;

        sf::Vector2f resetHighScrorePos;
        resetHighScrorePos.x = 130.0f;
        resetHighScrorePos.y = 264.8f;

        if (cursorPosition == quitEndMenu)
        {
            menu_cursor_s.setPosition(resetHighScrorePos);
            resetHighScore_txt.setFillColor(sf::Color::Red);
            endGameQuit_txt.setFillColor(sf::Color::Green);
        }

        if (cursorPosition == resetHighScrorePos)
        {
            menu_cursor_s.setPosition(quitEndMenu);
            resetHighScore_txt.setFillColor(sf::Color::Green);
            endGameQuit_txt.setFillColor(sf::Color::Red);
        }
    }
}

void ScreenManager::processCursorEvents()
{
    sf::Vector2f cursorPosition = menu_cursor_s.getPosition();
    sf::Vector2f cursorInGameInstructions;
    cursorInGameInstructions.x = 232.0f;
    cursorInGameInstructions.y = 400.0f;

    sf::Vector2f quitGameEndMenu;
    quitGameEndMenu.x = 173.0f;
    quitGameEndMenu.y = 289.8f;

    sf::Vector2f resetHighScorePos;
    resetHighScorePos.x = 130.0f;
    resetHighScorePos.y = 264.8f;

    if (inMainMenu)
    {
        if (viewingInstructions && cursorPosition == cursorInGameInstructions)
        {
            viewingInstructions = false;
            menu_cursor_s.setPosition(cursorInstructionsPos);
        }
        if (cursorPosition == cursorStartGamePos)
        {
            isPlaying = true;
            inMainMenu = false;
        }
        if (cursorPosition == cursorQuitGamePos)
        {
            window.close();
        }
        if (cursorPosition == cursorInstructionsPos)
        {
            viewingInstructions = true;
            bulletPoint1_watch->restart();
            bulletPoint2_watch->restart();
            bulletPoint3_watch->restart();
            bulletPoint4_watch->restart();
            bulletPoint5_watch->restart();
            scorpion_enemy_watch->restart();
            segment_enemy_watch->restart();
            flea_enemy_watch->restart();

            menu_cursor_s.setPosition(cursorInGameInstructions);
        }
    }

    if (inEndMenu)
    {
        if (cursorPosition == quitGameEndMenu)
            window.close();

        if (cursorPosition == resetHighScorePos)
        {
            auto high_score = score_manager.getHighScore();
            score_manager.reset_high_score();
            shared_ptr<StopWatch>timer = std::make_shared<StopWatch>();

            while (high_score > 0)
            {
                scoreResetEndMenu();
                auto time = timer->getTimeElapsed();
                std::string highScore = std::to_string(high_score);
                highestScore.setString(highScore);
                centerText(highestScore, 245.0f);
                window.draw(highestScore);
                window.display();
                window.clear();

                if (time >= 0.03f)
                {
                    if (high_score > 1000)
                    {
                        high_score -= 500;
                    }
                    if (high_score > 50 && high_score <= 1000)
                    {
                        high_score -= 50;
                    }
                    if (high_score <= 50)
                    {
                        --high_score;
                    }
                    timer->restart();
                }
                
            }
        }
    }
}

void ScreenManager::bulletPointAnimation(sf::Sprite& bulletPoint_sprite, shared_ptr<StopWatch>& bulletPoint_watch)
{
    if (bulletPoint_watch->getTimeElapsed() > 0.3f)
        bulletPoint_watch->restart();

    auto time = bulletPoint_watch->getTimeElapsed();
    if (time >= 0.0f && time <= 0.15f)
        bulletPoint_sprite.setTexture(bulletPoint1_t);

    if (time > 0.15f && time <= 0.3f)
    {
        bulletPoint_sprite.setTexture(bulletPoint2_t);
    }    
}

void ScreenManager::displayGameInstructions()
{
    bulletPointAnimation(instruction1_bulletPoint_s, bulletPoint1_watch);
    bulletPointAnimation(instruction2_bulletPoint_s, bulletPoint2_watch);
    bulletPointAnimation(instruction3_bulletPoint_s, bulletPoint3_watch);
    bulletPointAnimation(instruction4_bulletPoint_s, bulletPoint4_watch);
    bulletPointAnimation(instruction5_bulletPoint_s, bulletPoint5_watch);

    window.draw(instructions_background_s);
    window.draw(game_instruction1_txt);
    window.draw(game_instruction2_txt);
    window.draw(game_instruction3_txt);
    window.draw(game_instruction4_txt);
    window.draw(game_instruction5_txt);

    window.draw(instruction1_bulletPoint_s);
    window.draw(instruction2_bulletPoint_s);
    window.draw(instruction3_bulletPoint_s);
    window.draw(instruction4_bulletPoint_s);
    window.draw(instruction5_bulletPoint_s);

    window.draw(backToMainMenu_txt);
    window.draw(menu_cursor_s);

    displayEnemyList();
}

void ScreenManager::displayEnemyList()
{
    displayScorpionEnemy();
    displaySpiderEnemy();
    displayCentipedeEnemy();
    displayFleaEnemy();
}

void ScreenManager::displayScorpionEnemy()
{
    if (scorpion_enemy_watch->getTimeElapsed() > 4 * animation_period)
        scorpion_enemy_watch->restart();

    auto time = scorpion_enemy_watch->getTimeElapsed();
    if (time >= 0.0f && time <= animation_period)
        scorpion_enemy_s.setTexture(scorpion1_enemy_t);

    if (time > animation_period && time <= 2 * animation_period)
        scorpion_enemy_s.setTexture(scorpion2_enemy_t);

    if (time > 2 * animation_period && time <= 3 * animation_period)
        scorpion_enemy_s.setTexture(scorpion3_enemy_t);

    if (time > 3 * animation_period && time <= 4 * animation_period)
        scorpion_enemy_s.setTexture(scorpion4_enemy_t);

    window.draw(scorpion_enemy_s);
    window.draw(scorpion_instructions_txt);
}

void ScreenManager::displaySpiderEnemy()
{
    if (spider_enemy_watch->getTimeElapsed() > 8 * animation_period)
        spider_enemy_watch->restart();

    auto time = spider_enemy_watch->getTimeElapsed();
    if (time >= 0.0f && time <= animation_period)
        spider_enemy_s.setTexture(spider1_enemy_t);

    if (time > animation_period && time <= 2 * animation_period)
        spider_enemy_s.setTexture(spider2_enemy_t);

    if (time > 2 * animation_period && time <= 3 * animation_period)
        spider_enemy_s.setTexture(spider3_enemy_t);

    if (time > 3 * animation_period && time <= 4 * animation_period)
        spider_enemy_s.setTexture(spider4_enemy_t);

    if (time > 4 * animation_period && time <= 5 * animation_period)
        spider_enemy_s.setTexture(spider5_enemy_t);

    if (time > 5 * animation_period && time <= 6 * animation_period)
        spider_enemy_s.setTexture(spider6_enemy_t);

    if (time > 6 * animation_period && time <= 7 * animation_period)
        spider_enemy_s.setTexture(spider7_enemy_t);

    if (time > 7 * animation_period && time <= 8 * animation_period)
        spider_enemy_s.setTexture(spider8_enemy_t);

    window.draw(spider_enemy_s);
    window.draw(spider_instructions_txt);
}

void ScreenManager::displayCentipedeEnemy()
{
    if (segment_enemy_watch->getTimeElapsed() > 8 * animation_period)
        segment_enemy_watch->restart();

    auto time = segment_enemy_watch->getTimeElapsed();
    if (time >= 0.0f && time <= animation_period)
        segment_enemy_s.setTexture(segment1_enemy_t);

    if (time > animation_period && time <= 2 * animation_period)
        segment_enemy_s.setTexture(segment2_enemy_t);

    if (time > 2 * animation_period && time <= 3 * animation_period)
        segment_enemy_s.setTexture(segment3_enemy_t);

    if (time > 3 * animation_period && time <= 4 * animation_period)
        segment_enemy_s.setTexture(segment4_enemy_t);

    if (time > 4 * animation_period && time <= 5 * animation_period)
        segment_enemy_s.setTexture(segment5_enemy_t);

    if (time > 5 * animation_period && time <= 6 * animation_period)
        segment_enemy_s.setTexture(segment6_enemy_t);

    if (time > 6 * animation_period && time <= 7 * animation_period)
        segment_enemy_s.setTexture(segment7_enemy_t);

    if (time > 7 * animation_period && time <= 8 * animation_period)
        segment_enemy_s.setTexture(segment8_enemy_t);

    window.draw(segment_enemy_s);
    window.draw(centipede_instructions_txt);
}

void ScreenManager::displayFleaEnemy()
{
    if (segment_enemy_watch->getTimeElapsed() > 4 * animation_period)
        flea_enemy_watch->restart();

    auto time = flea_enemy_watch->getTimeElapsed();
    if (time >= 0.0f && time <= animation_period)
        flea_enemy_s.setTexture(flea1_enemy_t);

    if (time > animation_period && time <= 2 * animation_period)
        flea_enemy_s.setTexture(flea2_enemy_t);

    if (time > 2 * animation_period && time <= 3 * animation_period)
        flea_enemy_s.setTexture(flea3_enemy_t);

    if (time > 3 * animation_period && time <= 4 * animation_period)
        flea_enemy_s.setTexture(flea4_enemy_t);

    window.draw(flea_enemy_s);
    window.draw(flea_instructions_txt);
}

void ScreenManager::displayWinningMenu()
{
    window.draw(instructions_background_s);

    centerText(playerScoreTag, 170.0f);
    window.draw(playerScoreTag);

    auto current_score = logic.get_score();
    std::string _currentScore = std::to_string(current_score);
    playerScore.setString(_currentScore);
    centerText(playerScore, 195.0f);
    window.draw(playerScore);

    centerText(highestScoreTag, 220.0f);
    window.draw(highestScoreTag);

    auto high_score = score_manager.getHighScore();
    std::string highScore = std::to_string(high_score);
    highestScore.setString(highScore);
    centerText(highestScore, 245.0f);
    window.draw(highestScore);

    centerText(resetHighScore_txt, 270);
    window.draw(resetHighScore_txt);

    centerText(endGameQuit_txt, 295.0f);
    window.draw(endGameQuit_txt);

    window.draw(menu_cursor_s);
}

void ScreenManager::scoreResetEndMenu()
{
    window.draw(instructions_background_s);

    centerText(playerScoreTag, 170.0f);
    window.draw(playerScoreTag);

    auto current_score = logic.get_score();
    std::string _currentScore = std::to_string(current_score);
    playerScore.setString(_currentScore);
    centerText(playerScore, 195.0f);
    window.draw(playerScore);

    centerText(highestScoreTag, 220.0f);
    window.draw(highestScoreTag);

    centerText(resetHighScore_txt, 270);
    window.draw(resetHighScore_txt);

    centerText(endGameQuit_txt, 295.0f);
    window.draw(endGameQuit_txt);

    window.draw(menu_cursor_s);
}

void ScreenManager::centerText(sf::Text& text, float Yposition)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(windowWidth / 2.0f, Yposition));
}

void ScreenManager::load_resources()
{
    scorpion1_enemy_t.loadFromFile("resources/scorpion1-instruction.png");
    scorpion2_enemy_t.loadFromFile("resources/scorpion2-instruction.png");
    scorpion3_enemy_t.loadFromFile("resources/scorpion3-instruction.png");
    scorpion4_enemy_t.loadFromFile("resources/scorpion4-instruction.png");

    spider1_enemy_t.loadFromFile("resources/spider1-instruction.png");
    spider2_enemy_t.loadFromFile("resources/spider2-instruction.png");
    spider3_enemy_t.loadFromFile("resources/spider3-instruction.png");
    spider4_enemy_t.loadFromFile("resources/spider4-instruction.png");
    spider5_enemy_t.loadFromFile("resources/spider5-instruction.png");
    spider6_enemy_t.loadFromFile("resources/spider6-instruction.png");
    spider7_enemy_t.loadFromFile("resources/spider7-instruction.png");
    spider8_enemy_t.loadFromFile("resources/spider8-instruction.png");

    segment1_enemy_t.loadFromFile("resources/head1-instruction.png");
    segment2_enemy_t.loadFromFile("resources/head2-instruction.png");
    segment3_enemy_t.loadFromFile("resources/head3-instruction.png");
    segment4_enemy_t.loadFromFile("resources/head4-instruction.png");
    segment5_enemy_t.loadFromFile("resources/head5-instruction.png");
    segment6_enemy_t.loadFromFile("resources/head6-instruction.png");
    segment7_enemy_t.loadFromFile("resources/head7-instruction.png");
    segment8_enemy_t.loadFromFile("resources/head8-instruction.png");

    flea1_enemy_t.loadFromFile("resources/flea1-instruction.png");
    flea2_enemy_t.loadFromFile("resources/flea2-instruction.png");
    flea3_enemy_t.loadFromFile("resources/flea3-instruction.png");
    flea4_enemy_t.loadFromFile("resources/flea4-instruction.png");

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
    shot_centipede_segment_sprites.clear();
}

