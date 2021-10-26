#include "centipedeAnimation.h"

void centipedeAnimation::Animate(shared_ptr<Centipede>& centipede_ptr, shared_ptr<Sprite>& centipede_sprite)
{
    auto loop_counter = centipede_ptr -> get_anime_loop();
    auto head_ = centipede_ptr -> getHead();

    if (head_ == true)
    {
        //std::cout << "came here!!" << std::endl;
        if(loop_counter == 0)
        {
            head_texture.loadFromFile("resources/head1.png");
            centipede_sprite -> setTexture(head_texture);
        }

        if (loop_counter == 3)
        {
            head_texture.loadFromFile("resources/head2.png");
            centipede_sprite -> setTexture(head_texture);
        }

        if(loop_counter == 6)
        {
            head_texture.loadFromFile("resources/head3.png");
            centipede_sprite ->setTexture(head_texture);
        }

        if(loop_counter == 9)
        {
            head_texture.loadFromFile("resources/head4.png");
            centipede_sprite ->setTexture(head_texture);
        }

        if(loop_counter == 12)
        {
            head_texture.loadFromFile("resources/head5.png");
            centipede_sprite ->setTexture(head_texture);
        }

        if(loop_counter == 15)
        {
            head_texture.loadFromFile("resources/head6.png");
            centipede_sprite ->setTexture(head_texture);
        }

        if(loop_counter == 18)
        {
            head_texture.loadFromFile("resources/head7.png");
            centipede_sprite ->setTexture(head_texture);
        }

        if(loop_counter == 21)
        {
            head_texture.loadFromFile("resources/head8.png");
            centipede_sprite ->setTexture(head_texture);
            centipede_ptr -> reset_animation_loop();
        }
    }

    else
    {
        if(loop_counter == 0)
        {
            if(!segment_texture.loadFromFile("resources/body1.png")) throw CouldNotLoadPicture{};
            centipede_sprite -> setTexture(segment_texture);
        }

        if (loop_counter == 3)
        {
            if(!segment_texture.loadFromFile("resources/body2.png")) throw CouldNotLoadPicture{};
            centipede_sprite -> setTexture(segment_texture);
        }

        if(loop_counter == 6)
        {
            if(!segment_texture.loadFromFile("resources/body3.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
            centipede_ptr -> increment_animation();
        }

        if(loop_counter == 9)
        {
            if(!segment_texture.loadFromFile("resources/body4.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
        }

        if(loop_counter == 12)
        {
            if(!segment_texture.loadFromFile("resources/body5.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
            centipede_ptr -> increment_animation();
        }

        if(loop_counter == 15)
        {
            if(!segment_texture.loadFromFile("resources/body6.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
        }

        if(loop_counter == 18)
        {
            if(!segment_texture.loadFromFile("resources/body7.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
        }

        if(loop_counter == 21)
        {
            if(!segment_texture.loadFromFile("resources/body8.png")) throw CouldNotLoadPicture{};
            centipede_sprite ->setTexture(segment_texture);
            centipede_ptr -> reset_animation_loop();
        }
    }

    centipede_ptr -> increment_animation();

}
