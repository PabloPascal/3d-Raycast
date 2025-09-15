#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>
#include <vector>
#include <memory>

#include "map.h"
#include "Renderer.h"
#include "AI.h" 
#include "shotgun.hpp"
#include "EntityManager.hpp"

class Game
{

	Renderer* 				m_renderer = nullptr;

	sf::RenderWindow 		m_window;

	std::unique_ptr<Player> m_player;
	std::unique_ptr<Weapon> weapon;

	sf::Sprite 				weaponSprite;
	sf::Sprite 				aim;
	wallSprite 				wallSpriteInfo;

	ResourceManager* 		m_resources;
	EntityManager* 			m_EntityManager;

public:
	Game(const size_t screen_width, const size_t screen_height, 
		 const std::string& absolute_path);

	void run();

	~Game(){
		delete m_renderer;
	}

};


#endif // !ENGINE_H
