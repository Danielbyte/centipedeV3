#include "centipedeAnimation.h"

centipedeAnimation::centipedeAnimation()
{}

void centipedeAnimation::Animate(shared_ptr<Centipede>& centipede_ptr)
{
    auto loop_counter = centipede_ptr -> get_anime_loop();
  
    if(loop_counter == 21)
    {

        centipede_ptr -> reset_animation_loop();
    }
    centipede_ptr -> increment_animation();

}
