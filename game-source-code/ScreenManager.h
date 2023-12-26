#ifndef SCREENMANAGER_H
#define SCREENMANAGER
#include "GameDataType.h"
#include "Logic.h"
#include "MushroomField.h"
#include "Spider.h"
#include "ScoreManager.h"
#include "mushroomResources.h"
#include "soundManager.h"

class ScreenManager
{
    public:
    //construct ScreenManager object
    ScreenManager();
    ~ScreenManager();
    void run();
    void draw_mushrooms();
    void update_game();
    //bool quit_game;
    //bool restart_game;

    //scorpion
    void create_scorpion();
    //decided to put shared pointer in a vector to be able to delete it.
    vector<shared_ptr<sf::Sprite>>scorpion_sprite_vector;

    //spider
    void create_spider();
    vector <shared_ptr<sf::Sprite>>spider_sprite_vector;

    vector<shared_ptr<sf::Sprite>>DDTBombs_spiteVector;
    vector <shared_ptr<sf::Sprite>> bulletSprites_vector;
    vector <shared_ptr<sf::Sprite>> CentipedeSprite_vector;
    vector<shared_ptr<sf::Sprite>> FleaSprite_vector;

    vector<shared_ptr<MushroomField>> mushField;
    vector <shared_ptr<sf::Sprite>> mushroom_sprites;

    sf::Texture playerSprite_texture;
    sf::Sprite player_sprite;
    bool quit_game;
    bool restart_game;
    bool reset_high_score;

    private:
        std::shared_ptr<GameResources> game_resources = std::make_shared<GameResources>();

        //Number of body segments to spawn after head
        int bodiesToSpawn;
        //list <CentipedeHead> std::iterator it;
        bool isPlaying;
        sf::RenderWindow window;
        sf::RenderWindow* _window;
        void initialize_screen();
        void initialize_player();

        //in game looping
        void process_events();
        void keyboard_handling(sf::Keyboard::Key, bool);
        void update();

        //create game sprites
        void create_laserShots();
        void create_enemy();
        void create_flea();

        //set up of display text and fonts
        sf::Font splash_screenFont;
        sf::Text splash_screenDisplay;
        sf::Text game_instructions;

        //Text to show remaining lives
        sf::Text playerLives_display;
        sf::Font Displays;

        //Show current score
        sf::Text currentScore_display;

        //show high score
        sf::Text highScore_display;

        //update screen manager
        void updateScreen_manager();

        Logic logic;
        Scoremanager score_manager;

        //game object sprites and textures


        sf::Texture centipedeHead_texture;

        sf::Texture flea_texture;


        //Laser shots

        sf::Texture bullet_texture;
        sf::Sprite bullet_sprite;

        int shoot_timer;

        bool isGameOver;

        //scorpion
        bool canSpawnScorpion;
        sf::Texture scorpion_texture;
      
        //spider
        sf::Texture spider_texture;

        //bombs
        sf::Texture bomb_texture;

        void create_bomb();

        //Update game entities
        void update_game_entities();
        void draw_game_entities();

        shared_ptr<SoundManager>sound_manager = make_shared<SoundManager>();

        vector<shared_ptr<sf::Sprite>>shot_centipede_segment_sprites;
};
#endif // SCREENMANAGER_H
