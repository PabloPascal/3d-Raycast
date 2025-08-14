#include "Weapon.h"
#include <map>
#include <SFML/System/Clock.hpp>

class Shotgun: public Weapon
{
    textureID m_texture;
    std::map<int, textureID> animations;
    int animation_key{};
    int animation_count{};

    float time;
    sf::Clock timer;


    bool shooting;


public:

    Shotgun(textureID texture_id);


    void update(float dt) override;
    void shoot() override; 
    void animate() override;
    void load_animation(textureID animation_id);
	inline textureID getTextureId() const override {return m_texture; }
};