#ifndef SOUND_MANAGER
#define SOUND_MANAGER

#include "defines.h"


#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <SFML/System/Clock.hpp>
#include <iostream>



class SoundManager{




	class SoundHandler{

		friend class SoundManager;
		std::string m_path_to_file;
		sf::SoundBuffer m_buffer;
		sf::Sound m_sound;

	public:


		SoundHandler(){}

		SoundHandler(std::string pathToFile){

			m_path_to_file = pathToFile;

			if(m_buffer.loadFromFile(pathToFile)){
				m_sound.setBuffer(m_buffer);
			}
			else{
				throw std::string("cannot open this file!\n");
			}

		}
	};



	std::map<soundID, std::unique_ptr<SoundHandler>> sounds;

public:
    
    SoundManager(){}

    void loadSound(soundID id, std::string path_to_sound);
    void play(soundID id);
};



#endif