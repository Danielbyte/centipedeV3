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

        sf::Text game_instructions_txt;
        sf::Text start_Game_txt;
        sf::Text quit_Game_txt;

        sf::Texture main_menu_t;
        sf::Sprite main_menu_s;

        sf::Texture menu_cursor_t;
        sf::Sprite menu_cursor_s;

        //Text to show remaining lives
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

        sf::Texture instructions_background_t;
        sf::Sprite instructions_background_s;

        void create_bomb();

        //Update game entities
        void update_game_entities();
        void draw_game_entities();

        shared_ptr<SoundManager>sound_manager = make_shared<SoundManager>();

        vector<shared_ptr<sf::Sprite>>shot_centipede_segment_sprites;

        bool playerBombed;

        sf::Sprite player_livesHUD_s;
        sf::Texture life1_t, lives2_t, lives3_t;
        void updatePlayerLivesHUD(const int lives);
        bool inMainMenu;

        void moveCursorDown();
        void moveCursorUp();
        sf::Vector2f cursorStartGamePos;
        sf::Vector2f cursorInstructionsPos;
        sf::Vector2f cursorQuitGamePos;
        void processCursorEvents();
        bool viewingInstructions;

        void displayGameInstructions();
        void displayEnemyList();
        void displayScorpionEnemy();
        void displaySpiderEnemy();
        void bulletPointAnimation(sf::Sprite& bulletPoint_sprite, shared_ptr<StopWatch>& bulletPoint_watch);

        shared_ptr<StopWatch> bulletPoint1_watch = std::make_shared<StopWatch>();
        shared_ptr<StopWatch> bulletPoint2_watch = std::make_shared<StopWatch>();
        shared_ptr<StopWatch> bulletPoint3_watch = std::make_shared<StopWatch>();
        shared_ptr<StopWatch> bulletPoint4_watch = std::make_shared<StopWatch>();
        shared_ptr<StopWatch> bulletPoint5_watch = std::make_shared<StopWatch>();

        //For animations that demonstrate a list of enemies
        shared_ptr<StopWatch> scorpion_enemy_watch = std::make_shared<StopWatch>();
        shared_ptr<StopWatch> spider_enemy_watch = std::make_shared<StopWatch>();

        sf::Text game_instruction1_txt;
        sf::Text game_instruction2_txt;
        sf::Text game_instruction3_txt;
        sf::Text game_instruction4_txt;
        sf::Text game_instruction5_txt;

        sf::Text scorpion_instructions_txt;
        sf::Text spider_instructions_txt;

        sf::Sprite instruction1_bulletPoint_s;
        sf::Sprite instruction2_bulletPoint_s;
        sf::Sprite instruction3_bulletPoint_s;
        sf::Sprite instruction4_bulletPoint_s;
        sf::Sprite instruction5_bulletPoint_s;

        sf::Texture bulletPoint1_t, bulletPoint2_t;

        sf::Texture scorpion1_enemy_t, scorpion2_enemy_t, scorpion3_enemy_t, scorpion4_enemy_t;
        sf::Sprite scorpion_enemy_s;

        sf::Texture spider1_enemy_t, spider2_enemy_t, spider3_enemy_t, spider4_enemy_t, spider5_enemy_t,
                    spider6_enemy_t, spider7_enemy_t, spider8_enemy_t;

        sf::Sprite spider_enemy_s;
        
        void load_resources();
        float animation_period;

};
#endif // SCREENMANAGER_H
