#ifndef SHOTGUN_HPP
#define SHOTGUN_HPP

#include "Weapon.h"
#include <map>
#include <SFML/System/Clock.hpp>
#include "animationSystem.hpp"
#include "soundSystem.hpp"


class Shotgun: public Weapon
{
    textureID m_texture;
    
    std::unique_ptr<Animation> animate = nullptr;
    soundID m_sound;

    bool m_shooting;
    float m_TimeCooldown;
    sf::Clock timer;

public:

    Shotgun(textureID texture_id, soundID sound_id);


    void update(float dt) override;

    void shoot() override; 

    void animating() override;
    void load_animation(textureID animation_id);
	inline textureID getTextureId() const override {return m_texture; }
    inline soundID getSoundID() override {return m_sound;}
    bool getShootIndicate() override {return m_shooting;}
    inline void setCooldownTime(float time_as_millisec) override {m_TimeCooldown = time_as_millisec;}

};



#endif //SHOTGUN_HPP