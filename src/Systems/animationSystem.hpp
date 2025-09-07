#ifndef ANIMATION_SYS
#define ANIMATION_SYS

#include <istream>
#include <vector>
#include "defines.h"
#include <SFML/System/Clock.hpp>
#include <functional>

class Animation{
    using animation_key = unsigned int;

    animation_key current_key;

    textureID curr_anim_id;
    std::vector<textureID> animations;
    float delay_time;
    sf::Clock timer;
public:
    Animation() : current_key(0), delay_time(0){}
    Animation(textureID default_animation, float delay_time);

    void set_animation(textureID texId);
    void remove_animation(textureID target_id);
    textureID getCurrentAnimation();

    void update(std::function<void()> func = []{});
};



#endif //ANIMATION_SYS