#include "centipedeAnimation.h"

void centipedeAnimation::Animate(shared_ptr<Centipede>& centipede_ptr, shared_ptr<Sprite>& centipede_sprite)
{
    auto loop_counter = centipede_ptr -> get_anime_loop();
    auto head = centipede_ptr -> getHead();
    std::cout << loop_counter << std::endl;
    if(!head)
    {
        if(loop_counter == 0)
        {
            if(!segment_texture.loadFromFile("resources/body1.png")) throw CouldNotLoadPicture{};
            centipede_sprite -> setTexture(segment_texture);
        }

        if (loop_counter == 4)
        {
            if(!segment_texture.loadFromFile("resources/body2.png")) throw CouldNotLoadPicture{};
            centipede_sprite -> setTexture(segment_texture);
            //centipede_ptr -> increment_animation();
        }

        if(loop_counter == 8)
        {
            if(!segment_texture.loadFromFile("resources/body3.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
            centipede_ptr -> increment_animation();
        }

        if(loop_counter == 12)
        {
            if(!segment_texture.loadFromFile("resources/body4.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
            //centipede_ptr -> increment_animation();
        }

        if(loop_counter == 16)
        {
            if(!segment_texture.loadFromFile("resources/body5.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
            centipede_ptr -> increment_animation();
        }

        if(loop_counter == 20)
        {
            if(!segment_texture.loadFromFile("resources/body6.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
            //centipede_ptr -> increment_animation();
        }

        if(loop_counter == 24)
        {
            if(!segment_texture.loadFromFile("resources/body7.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
            //centipede_ptr -> increment_animation();
        }

        if(loop_counter == 28)
        {
            if(!segment_texture.loadFromFile("resources/body8.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
            centipede_ptr -> reset_animation_loop();
        }
    }

    else
    {
        //std::cout << "I am the head!!" << std::endl;
    }

    centipede_ptr -> increment_animation();

}
