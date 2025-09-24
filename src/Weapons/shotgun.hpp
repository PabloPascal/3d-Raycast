#ifndef SHOTGUN_HPP
#define SHOTGUN_HPP

#include "Weapon.h"
#include <map>
#include <SFML/System/Clock.hpp>
#include "animationSystem.hpp"
#include "soundSystem.hpp"
#include <SFML/Graphics/Sprite.hpp>


class Shotgun: public Weapon
{
    textureID   m_texture_id;
    soundID     m_sound_id;
    bool        m_isShooting;
    float       m_TimeCooldown;
    float       m_delay_time_animation;

    std::unique_ptr<Animation> animate = nullptr;
    sf::Clock timer;

    int m_bullets;
    int damage;
    sf::Sprite shotgun_sprite;

public:

    Shotgun(textureID texture_id, soundID sound_id,const sf::Vector2u& screen_resolve, int bullets = 10);


    void update(float dt) override;

    void shoot() override {}
    void shoot(Camera*) override;
    void animating() override;
    void load_animation(textureID animation_id);
    inline textureID getTextureId() const override {return m_texture_id; }
    inline soundID getSoundID() override {return m_sound_id;}
    bool getShootIndicate() override {return m_isShooting;}
    inline void setCooldownTime(float time_as_millisec) override {m_TimeCooldown = time_as_millisec;}
    void draw(sf::RenderWindow&) override;

};



#endif //SHOTGUN_HPP
