#include "shotgun.hpp"
#include <iostream>
#include "ResourceHolder.h"

Shotgun::Shotgun(textureID texture, soundID sound){

    m_texture = texture;
    m_sound = sound;
    m_shooting = false;
    m_TimeCooldown = 0;
    timer.restart();
    animate = std::make_unique<Animation>(m_texture, 200);
}


void Shotgun::shoot() {
    
    
    if(timer.getElapsedTime().asMilliseconds() >= m_TimeCooldown ){
        
        m_shooting = true;
        ResourceManager::getInstance()->play(m_sound);
        timer.restart();

    }
    


}


void Shotgun::animating(){

    

}


void Shotgun::load_animation(textureID animation_id){

    animate->set_animation(animation_id);

}


void Shotgun::update(float dt){



    if(m_shooting == true){
        animate->update([&]
            {
                m_shooting = false;
            });
        m_texture = animate->getCurrentAnimation();
        
        

    }
    

}