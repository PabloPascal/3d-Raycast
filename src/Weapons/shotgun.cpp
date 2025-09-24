#include "shotgun.hpp"
#include <iostream>
#include "ResourceHolder.h"
#include "raycast.h"


Shotgun::Shotgun(textureID texture, soundID sound, const sf::Vector2u& screen_resolve, int bullets) : m_bullets(bullets)
{

    m_texture_id = texture;
    m_sound_id = sound;
    m_isShooting = false;
    m_TimeCooldown = 0;
    m_delay_time_animation = 200;
    timer.restart();
    animate = std::make_unique<Animation>(m_texture_id, 200, true);

    shotgun_sprite.setTexture(ResourceManager::getInstance()->getTexture(textureID::weapon));
    shotgun_sprite.setOrigin(
        ResourceManager::getInstance()->getTexture(textureID::weapon).getSize().x/2.f, 
        ResourceManager::getInstance()->getTexture(textureID::weapon).getSize().y
    );
    shotgun_sprite.setScale(screen_resolve.x / 200.f, screen_resolve.y / 200.f);
    shotgun_sprite.setPosition(screen_resolve.x/2, screen_resolve.y);

    damage = 2;

}


void Shotgun::shoot(Camera* camera) {
    
    if(m_bullets > 0){

        if(timer.getElapsedTime().asMilliseconds() >= m_TimeCooldown ){

            m_bullets--;

            m_isShooting = true;
            ResourceManager::getInstance()->play(m_sound_id);

            int ray_origins[3] = {4,5,6};
            Ray hits[3] = {FastRayCast(*camera, ray_origins[0], mapID::default_map, 10, true),
                            FastRayCast(*camera, ray_origins[1], mapID::default_map, 10, true),
                            FastRayCast(*camera, ray_origins[2], mapID::default_map, 10, true)};


            for(int hit = 0; hit < 3; hit++){
                if(hits[hit].hitted_thing != nullptr){
                    hits[hit].hitted_thing->setHealth(hits[hit].hitted_thing->getHealth() - damage);
                    hits[hit].hitted_thing->set_damage_indicate(true);
                }
            }

            timer.restart();

        }
    }
    else{
        ResourceManager::getInstance()->play(soundID::no_bullet_sound);
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



void Shotgun::draw(sf::RenderWindow& window) {

    shotgun_sprite.setTexture(ResourceManager::getInstance()->getTexture(m_texture_id));
    window.draw(shotgun_sprite);

}
