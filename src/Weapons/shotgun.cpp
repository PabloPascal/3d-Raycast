#include "shotgun.hpp"
#include <iostream>


Shotgun::Shotgun(textureID texture, soundID sound){

    m_texture = texture;
    m_sound = sound;
    shooting = false;

    animate = std::make_unique<Animation>(m_texture, 200);
}


void Shotgun::shoot(){
    shooting = true;
}


void Shotgun::animating(){

    

}


void Shotgun::load_animation(textureID animation_id){

    animate->set_animation(animation_id);

}


void Shotgun::update(float dt){

    //std::cout << "isPlay: " << isPlay << std::endl;

    isPlay = false;

    if(shooting == true){
        animate->update([&]
            {
                shooting = false;
            });
        m_texture = animate->getCurrentAnimation();
        
    }
    

}