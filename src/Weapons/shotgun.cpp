#include "shotgun.hpp"
#include <iostream>
#include "ResourceHolder.h"

Shotgun::Shotgun(textureID texture, soundID sound){

    m_texture_id = texture;
    m_sound_id = sound;
    m_isShooting = false;
    m_TimeCooldown = 0;
    m_delay_time_animation = 200;
    timer.restart();
    animate = std::make_unique<Animation>(m_texture_id, 200, true);
}


void Shotgun::shoot() {
    
    
    if(timer.getElapsedTime().asMilliseconds() >= m_TimeCooldown ){
        
        m_isShooting = true;
        ResourceManager::getInstance()->play(m_sound_id);
        timer.restart();

    }
    


}


void Shotgun::animating(){}


void Shotgun::load_animation(textureID animation_id){

    animate->set_animation(animation_id);

}


void Shotgun::update(float dt){



    if(m_isShooting == true){
        animate->update([&]
            {
                m_isShooting = false;
            });
        m_texture_id = animate->getCurrentAnimation();
        
        

    }
    

}
