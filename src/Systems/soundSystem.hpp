#ifndef SOUND_MANAGER
#define SOUND_MANAGER
#include <iostream>
#include "defines.h"
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <SFML/System/Clock.hpp>

class SoundManager{


    std::map<soundID, sf::Sound> sounds;
    sf::Clock timer;
    bool isPlaySound = false;


public:
    
    SoundManager(){}

    void loadSound(soundID id, std::string path_to_sound);
    void play(soundID id);
};



#endif