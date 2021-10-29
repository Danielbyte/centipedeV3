#ifndef SCREENMANAGER_H
#define SCREENMANAGER
#include "GameDataType.h"
#include "SfmlDataType.h"
#include "Logic.h"
#include "MushroomField.h"
#include "Spider.h"

class ScreenManager
{
    public:
    //construct ScreenManager object
    ScreenManager();
    ~ScreenManager();
    void run();
    void draw_mushrooms(const shared_ptr<MushroomFieldController>&);
    void update_game();

    //scorpion
    void create_scorpion();
    shared_ptr<Sprite>scorpion{new Sprite{}};

    //spider
    void create_spider();
    vector <shared_ptr<Sprite>>spider_sprite_vector;

    private:
        //Number of body segments to spawn after head
        int bodiesToSpawn;
        //list <CentipedeHead> std::iterator it;
        bool isPlaying;
        RenderWindow window;
        RenderWindow* _window;
        void initialize_screen();
        void initialize_player();

        //in game looping
        void process_events();
        void keyboard_handling(Keyboard, bool);
        void update();

        //create game sprites
        void create_laserShots();
        void create_enemy();

        //set up of display text and fonts
        Font splash_screenFont;
        Text splash_screenDisplay;
        Text game_instructions;

        //Text to show remaining lives
        Text playerLives_display;
        Font Displays;

        //update screen manager
        void updateScreen_manager();

        Logic logic;

        //game object sprites and textures
        Texture playerSprite_texture;
        Sprite player_sprite;
        Texture centipedeHead_texture;
        vector <shared_ptr<Sprite>> CentipedeSprite_vector;

        //Laser shots
        vector <shared_ptr<Sprite>> bulletSprites_vector;
        Texture bullet_texture;
        Sprite bullet_sprite;

        int shoot_timer;

        bool isGameOver;

        //scorpion
        bool canSpawnScorpion;
        Texture scorpion_texture;

        //spider
        Texture spider_texture;

        //bombs
        vector<shared_ptr<Sprite>>DDTBombs_spiteVector;
        Texture bomb_texture;
};
#endif // SCREENMANAGER_H
