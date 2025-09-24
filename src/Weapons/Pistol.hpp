#ifndef PISTOL_HPP
#define PISTOL_HPP


#include "Weapon.h"
#include "animationSystem.hpp"
#include "ResourceHolder.h"
#include "defines.h"
#include <SFML/Graphics/Sprite.hpp>


class Pistol : public Weapon
{

    float       m_damage;
    textureID   m_texture_id;
    soundID     m_sound_id;
    float       m_TimeCooldown;
    bool        m_isShooting;
    float       m_delay_time_animation;
    int         m_bullets;

    int         count_hits = 0;
    int         damage;

    std::unique_ptr<Animation> animate = nullptr;
    sf::Clock timer;

    sf::Sprite pistol_sprite;

public:

    Pistol(textureID texture_id, soundID sound_id, const sf::Vector2u& screen_resolve, int bullets = 30);

    void update(float dt) override;

    void shoot() override;
    void shoot(Camera* camera) override;
    void animating() override {}
    void load_animation(textureID animation_id);
    inline textureID getTextureId() const override {return m_texture_id; }
    inline soundID getSoundID() override {return m_sound_id;}
    bool getShootIndicate() override {return m_isShooting;}
    inline void setCooldownTime(float time_as_millisec) override {m_TimeCooldown = time_as_millisec;}
    void draw(sf::RenderWindow& window) override;

};





#endif // PISTOL_HPP
