#include "animationSystem.hpp"
#include <iostream>

Animation::Animation(textureID default_animation, float _delay_time /*millisec*/) : 
curr_anim_id(default_animation), current_key(0), delay_time(_delay_time)
{

    animations.push_back(default_animation);

}

void Animation::update(std::function<void()> func){

    if(timer.getElapsedTime().asMilliseconds() > delay_time){
        

        if(current_key < animations.size()-1){
            current_key++;
            
        }
        else{
            current_key = 0;
            func();
        }

		timer.restart();

	}
    curr_anim_id = animations[current_key];
}   

textureID Animation::getCurrentAnimation(){
    return curr_anim_id;
}

void Animation::set_animation(textureID texId){

    animations.push_back(texId);

}