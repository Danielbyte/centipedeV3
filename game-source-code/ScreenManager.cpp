#include "ScreenManager.h"
ScreenManager::ScreenManager():
    bodiesToSpawn{11}, //spawn 11 body segments
    isPlaying{false},
    window(VideoMode(windowWidth, windowHeight), "CENTIPEDE++"),
    shoot_timer{2},
    isGameOver{false}
{
    initialize_screen();
    initialize_player();
    create_enemy();
}

void ScreenManager::initialize_player()
{
    if(!playerSprite_texture.loadFromFile("resources/player.png")) throw CouldNotLoadPicture{};
    player_sprite.setTexture(playerSprite_texture);
    player_sprite.setPosition(logic.player_object.get_Xposition(), logic.player_object.get_Yposition());
    player_sprite.setOrigin(vector2f(player_size/2, player_size/2));
}

void ScreenManager::initialize_screen()
{
    Displays.loadFromFile("resources/sansation.ttf");
    splash_screenFont.loadFromFile("resources/sansation.ttf");
    splash_screenDisplay.setFont(splash_screenFont);
    splash_screenDisplay.setCharacterSize(20);
    splash_screenDisplay.setStyle(Text::Regular);
    splash_screenDisplay.setFillColor(Color::Red);
    splash_screenDisplay.setPosition(10,180);
    splash_screenDisplay.setString("Welcome to Centipede++");

    //game instructions set up
    game_instructions.setFont(splash_screenFont);
    game_instructions.setCharacterSize(20);
    game_instructions.setStyle(Text::Regular);
    game_instructions.setFillColor(Color::Red);
    game_instructions.setPosition(10, 220);
    game_instructions.setString("INSTRUCTIONS: \nPress Enter to start game!"
                                "\nPress Escape(Esc) to quit!"
                                "\nUse keyboard arrows to move player"
                                "\nPress space to shoot");

    playerLives_display.setFont(Displays);
    playerLives_display.setCharacterSize(12);
    playerLives_display.setStyle(Text::Underlined);
    playerLives_display.setFillColor(Color::Red);
    playerLives_display.setPosition(0,0);

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
            window.draw(player_sprite);

            for (auto& centipede_segments : CentipedeSprite_vector) // draw centipede (only the head for now)
            {
                window.draw(*centipede_segments);
            }

            for (auto& bullet : bulletSprites_vector) // draw bullets on screen
            {
                //(bullet) ->Draw(_window);
                window.draw(*bullet);
            }

            window.draw(*scorpion);

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

void ScreenManager::process_events()
{
    Event event;
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case Event::KeyPressed:
            if(event.key.code == Keyboard::Escape)
            {
                window.close();
            }
            else
                keyboard_handling(event.key.code, true);
            break;

        case Event::KeyReleased:
            keyboard_handling(event.key.code, false);
            break;

        case Event::Closed:
            window.close();
            break;

        default:
            ;

        }
    }
}

void ScreenManager::keyboard_handling(Keyboard key, bool isPressed)
{
    if (shoot_timer < 2)
    {
        shoot_timer++;
    }

    if(key == Keyboard::Enter) //player wants to play
        isPlaying = true;
    if(isPlaying)
    {
        if(key == Keyboard::Up)
        {
            logic.player_object.setPlayer_movement(Direction::Up, isPressed);
        }
        else if(key == Keyboard::Down)
        {
            //player should move down
            logic.player_object.setPlayer_movement(Direction::Down, isPressed);
        }
        else if(key == Keyboard::Right)
        {
            //player should move right
            logic.player_object.setPlayer_movement(Direction::Right, isPressed);
        }
        else if(key == Keyboard::Left)
        {
            //player should move down
            logic.player_object.setPlayer_movement(Direction::Left, isPressed);
        }
        else if (key == Keyboard::Space && shoot_timer >= 2)
        {
            create_laserShots();
            shoot_timer = 0;
        }
    }
}

void ScreenManager::update()
{
    auto mushGridPtr = logic.GetMushGridPtr();
    draw_mushrooms(mushGridPtr);

    logic.update_player(player_sprite);
    logic.updateLaserShots(bulletSprites_vector);
    logic.update_centipede(CentipedeSprite_vector);
    logic.collisionBetween_mushAndPlayer(player_sprite);
    logic.collisionBetweenBulletsAndObjects(bulletSprites_vector, CentipedeSprite_vector);
    logic.collision_between_mush_and_spider();
    logic.collision_between_player_and_spider(player_sprite);
    logic.collision_btwn_bullet_and_spider(bulletSprites_vector, spider_sprite_vector);
    logic.collision_between_bullet_and_bomb(bulletSprites_vector, DDTBombs_spiteVector, spider_sprite_vector);


    //scorpion updates
    auto canSpawnScorpion = logic.canSpawn_scorpion();

    if (canSpawnScorpion)
    {
        create_scorpion();
    }
    logic.update_scorpion(scorpion);

    //spider updates
    auto canSpawnSpider = logic.getIfCanSpawnSpider();
    if(canSpawnSpider && (spider_sprite_vector.empty()))
    {
        //time to create a spider!
        create_spider();
    }

    logic.update_spider(spider_sprite_vector);

    //query logic if can spawn bomb
    auto canSpawnBomb = logic.getIfCanSpawnBomb();
    if(canSpawnBomb)
    {
        //request logic to create bomb
        create_bomb();
    }

    //std::cout<< "Here" <<std::endl;

    updateScreen_manager();
    update_game();
    //std::cout << "Malasti" << std::endl;
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
    vector2f pos_ = logic.create_scorpion();
    if(!scorpion_texture.loadFromFile("resources/scorpion1.png")) throw CouldNotLoadPicture{};
    scorpion -> setOrigin(vector2f(scorpion_width/2.f, scorpion_height/2.f));
    scorpion -> setTexture(scorpion_texture);
    scorpion -> setPosition(pos_);
}

void ScreenManager::create_spider()
{
    vector2f pos_ = logic.create_spider();
    auto spider_sprite = std::make_shared<Sprite>(Sprite());
    if(!spider_texture.loadFromFile("resources/spider1.png")) throw CouldNotLoadPicture{};
    spider_sprite -> setOrigin(vector2f(spiderWidth/2.f, spiderHeight/2.f));
    spider_sprite -> setTexture(spider_texture);
    spider_sprite -> setPosition(pos_);
    spider_sprite_vector.push_back(spider_sprite);
}

void ScreenManager::create_bomb()
{
    vector2f pos = logic.create_bomb();
    auto bomb_sprite = std::make_shared<Sprite>(Sprite());
    if(!bomb_texture.loadFromFile("resources/bomb1.png")) throw CouldNotLoadPicture{};
    bomb_sprite ->setTexture(bomb_texture);
    bomb_sprite -> setOrigin(vector2f(8.f, 8.f));
    bomb_sprite -> setPosition(pos);
    DDTBombs_spiteVector.push_back(bomb_sprite);
}

void ScreenManager::draw_mushrooms(const shared_ptr<MushroomFieldController>& MushGridPtr)
{
    Texture mushroomTexture;
    Sprite mushroomSprite;
    mushroomTexture.loadFromFile("resources/mushroom.png", intRect(0,0,16,16)); // crop off the first frame only.
    mushroomSprite.setTexture(mushroomTexture);

    Texture mushroomTexture_;
    Sprite mushroomSprite_;


    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if(MushGridPtr ->mushArray[i][j] != NULL)
            {
                auto mush_health = MushGridPtr ->mushArray[i][j] -> getMush_health();
                auto isPoisoned = MushGridPtr ->mushArray[i][j] -> getIsPoisoned();
                if (isPoisoned == false)
                {
                    if (mush_health == 4)
                    {
                        mushroomSprite.setOrigin(vector2f(0, 0));
                        mushroomSprite.setScale(1,1);
                        mushroomSprite.setPosition(j*offset, i*offset);
                        window.draw(mushroomSprite);
                    }
                    //std::cout << "I'm a dying mush "<< mush_health<< std::endl;
                    if (mush_health == 3)
                    {

                        mushroomTexture_.loadFromFile("resources/mush1.png");
                        mushroomSprite_.setTexture(mushroomTexture_);
                        mushroomSprite_.setOrigin(vector2f(0.f, 0.f));
                        mushroomSprite_.setPosition(j*offset, i*offset);
                        window.draw(mushroomSprite_);
                    }
                    if (mush_health == 2)
                    {
                        mushroomTexture_.loadFromFile("resources/mush2.png");
                        mushroomSprite_.setTexture(mushroomTexture_);
                        mushroomSprite_.setOrigin(vector2f(0.f, 0.f));
                        mushroomSprite_.setPosition(j*offset, i*offset);
                        window.draw(mushroomSprite_);
                    }

                    if (mush_health == 1)
                    {
                        mushroomTexture_.loadFromFile("resources/mush3.png");
                        mushroomSprite_.setTexture(mushroomTexture_);
                        mushroomSprite_.setOrigin(vector2f(0.f, 0.f));
                        mushroomSprite_.setPosition(j*offset, i*offset);
                        window.draw(mushroomSprite_);
                    }
                }

                if(isPoisoned)
                {
                    if (mush_health == 4)
                    {
                        mushroomTexture_.loadFromFile("resources/pmush1.png");
                        mushroomSprite_.setTexture(mushroomTexture_);
                        mushroomSprite_.setOrigin(vector2f(0.f, 0.f));
                        mushroomSprite_.setPosition(j*offset, i*offset);
                        window.draw(mushroomSprite_);
                    }
                    if (mush_health == 3)
                    {

                        mushroomTexture_.loadFromFile("resources/pmush2.png");
                        mushroomSprite_.setTexture(mushroomTexture_);
                        mushroomSprite_.setOrigin(vector2f(0.f, 0.f));
                        mushroomSprite_.setPosition(j*offset, i*offset);
                        window.draw(mushroomSprite_);
                    }
                    if (mush_health == 2)
                    {
                        mushroomTexture_.loadFromFile("resources/pmush3.png");
                        mushroomSprite_.setTexture(mushroomTexture_);
                        mushroomSprite_.setOrigin(vector2f(0.f, 0.f));
                        mushroomSprite_.setPosition(j*offset, i*offset);
                        window.draw(mushroomSprite_);
                    }

                    if (mush_health == 1)
                    {
                        mushroomTexture_.loadFromFile("resources/pmush4.png");
                        mushroomSprite_.setTexture(mushroomTexture_);
                        mushroomSprite_.setOrigin(vector2f(0.f, 0.f));
                        mushroomSprite_.setPosition(j*offset, i*offset);
                        window.draw(mushroomSprite_);
                    }

                }

            }
        }
    }
}

void ScreenManager::updateScreen_manager()
{
    auto remainingPlayer_lives = logic.player_object.getPlayer_lives();
    std::string remainingPlayer_lives_ = std::to_string(remainingPlayer_lives);
    playerLives_display.setString("LIVES: " + remainingPlayer_lives_);
    window.draw(playerLives_display);

}

void ScreenManager::update_game()
{
    splash_screenDisplay.setPosition(125, 208);
    splash_screenDisplay.setCharacterSize(40);

    // Game should terminate if player lives = zero
    // see if player is still alive
    auto player_status = logic.player_object.getPlayer_state();
    if(!player_status)
    {
        isPlaying = false;
        isGameOver = true;
        splash_screenDisplay.setString("YOU LOST!"
                                       "\nGAME OVER");
    }

    auto killed_segments = logic.getKilled_segments();
    auto centipede_size = bodiesToSpawn + 1;
    if(killed_segments == centipede_size)
    {
        isPlaying = false;
        isGameOver = true;
        splash_screenDisplay.setString("YOU WIN!"
                                       "\nGAME OVER");
    }
}

//Free up resources
ScreenManager::~ScreenManager()
{
    bulletSprites_vector.clear();
    CentipedeSprite_vector.clear();
}
