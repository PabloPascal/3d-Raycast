#include <iostream>
#include "Pistol.hpp"
#include "raycast.h"
#include "Demon.h"

Pistol::Pistol(textureID texture_id, soundID sound_id, int bullets) : m_bullets(bullets)
{

    m_texture_id = texture_id;
    m_sound_id = sound_id;
    m_isShooting = false;
    m_TimeCooldown = 0;
    m_delay_time_animation = 50;
    timer.restart();
    animate = std::make_unique<Animation>(m_texture_id, m_delay_time_animation, true);

}


void Pistol::shoot(){}


void Pistol::shoot(Camera* camera) 
{
    
    if(m_bullets > 0){



        if(timer.getElapsedTime().asMilliseconds() >= m_TimeCooldown ){
            
            m_bullets--;

            m_isShooting = true;
            ResourceManager::getInstance()->play(m_sound_id);

            Ray hit = FastRayCast(*camera, 1, mapID::default_map, 2, true);
            if(hit.hitted_thing != nullptr){
                count_hits++;
                hit.hitted_thing->setHealth(hit.hitted_thing->getHealth() - 1);
            }

            timer.restart();

            std::cout << "bullet remain: " << m_bullets << std::endl;

        }


    }
    else{
        ResourceManager::getInstance()->play(soundID::no_bullet_sound);
    }
    
}



void Pistol::load_animation(textureID animation_id){

    animate->set_animation(animation_id);

}


void Pistol::update(float dt){


    if(m_isShooting == true){
        animate->update([&]
            {
                m_isShooting = false;
            });
        m_texture_id = animate->getCurrentAnimation();

    }
    

}