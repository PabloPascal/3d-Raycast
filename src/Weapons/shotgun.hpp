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

    bool isPlay = false;

    bool shooting;
    
public:

    Shotgun(textureID texture_id, soundID sound_id);


    void update(float dt) override;
    void shoot() override; 
    void animating() override;
    void load_animation(textureID animation_id);
	inline textureID getTextureId() const override {return m_texture; }
    inline soundID getSoundID() override {return m_sound;}
    bool getShootIndicate() override {return isPlay;}
};