#include "soundSystem.hpp"



void SoundManager::loadSound(soundID id, std::string path_to_sound){

    sf::SoundBuffer buffer;
    buffer.loadFromFile(path_to_sound);
    sf::Sound sound(buffer);
    sounds.insert(std::make_pair(id, sound));

    std::cout << "load SOund\n";

    sounds[id].play();


}



void SoundManager::play(soundID id){

    // if(timer.getElapsedTime().asMilliseconds() < 3000){
    //     sounds[id].play();
    //     std::cout << sounds[id].getStatus();
    //     timer.restart();
    // }

    sounds[id].play();
    std::cout << sounds[id].getBuffer()->getSampleCount() << std::endl;
}
