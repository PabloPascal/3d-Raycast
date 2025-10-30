#include <iostream>
#include "Pistol.hpp"
#include "raycast.h"
#include "Demon.h"
#include <cmath>

Pistol::Pistol(textureID texture_id, soundID sound_id,const sf::Vector2u& screen_resolve, int bullets) : m_bullets(bullets)
{

    m_texture_id = texture_id;
    m_sound_id = sound_id;
    m_isShooting = false;
    m_TimeCooldown = 0;
    m_delay_time_animation = 50;
    timer.restart();
    animate = std::make_unique<Animation>(m_texture_id, m_delay_time_animation, true);


    pistol_sprite.setTexture(ResourceManager::getInstance()->getTexture(textureID::pistol_0));
	pistol_sprite.setOrigin(sf::Vector2f(ResourceManager::getInstance()->getTexture(textureID::pistol_0).getSize()));
	pistol_sprite.scale({ 1.5f * (float)screen_resolve.x / 400.f, 1.5f * (float)screen_resolve.y / 300.f});
	sf::Vector2u tex_size = ResourceManager::getInstance()->getTexture(textureID::weapon).getSize();
	pistol_sprite.setPosition(sf::Vector2f(screen_resolve.x, screen_resolve.y));

    damage = 5;

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
                
                //std::cout << "height hit: " << hit.dist / std::cos(myMATH::PI * camera->pitch / 500.f) << std::endl;
                if(hit.dist / std::cos(myMATH::PI * camera->pitch / 500.f) < hit.hitted_thing->get_height())
                {
                    //std::cout << "pitch = " << camera->pitch << std::endl;
                    hit.hitted_thing->set_damage_indicate(true);
                }
            }

            timer.restart();

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



void Pistol::draw(sf::RenderWindow& window) 
{
    pistol_sprite.setTexture(ResourceManager::getInstance()->getTexture(m_texture_id));
    window.draw(pistol_sprite);
}
