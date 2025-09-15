#include "soundSystem.hpp"

#include <assert.h>

void SoundManager::loadSound(soundID id, std::string path_to_sound){


    sounds.insert(std::make_pair(id, new 
        SoundHandler(path_to_sound)
        ));

}



void SoundManager::play(soundID id){


    if(sounds.find(id) == sounds.end()){
        std::cout << "no this sound!\n";
        return;
    }


    sounds[id]->m_sound.play();
}
