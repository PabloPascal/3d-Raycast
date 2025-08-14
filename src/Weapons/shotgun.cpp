#include "shotgun.hpp"
#include <iostream>


Shotgun::Shotgun(textureID texture){

    m_texture = texture;
    shooting = false;

}


void Shotgun::shoot(){
    shooting = true;

}


void Shotgun::animate(){

    time += timer.getElapsedTime().asSeconds();

    if(time > 1){

        if(animation_key < animation_count){

            m_texture = animations[animation_key];
            animation_key++;

        }
        else{
            animation_key = 0;
            m_texture = animations[animation_key];
            shooting = false;
        }

        time = 0;
        timer.restart();
    }

}


void Shotgun::load_animation(textureID animation_id){

    animations.insert(std::make_pair(animation_count, animation_id));
    animation_count++;

}


void Shotgun::update(float dt){

    if(shooting == true){
        animate();
    }
    

}