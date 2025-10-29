#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <vector>
#include <memory>

#include "map.h"
#include "Renderer.h"
#include "AI.h" 
#include "shotgun.hpp"
#include "EntityManager.hpp"
#include "debug_ui.hpp"

class Game
{

	Renderer* 				m_renderer = nullptr;

	sf::RenderWindow 		m_window;

	std::unique_ptr<Player> m_player;
	Weapon* weapon;
	Camera*					g_camera;

	sf::Sprite 				aim;
	wallSprite 				wallSpriteInfo;


	ResourceManager* 		m_resources;
	EntityManager* 			m_EntityManager;


	//weapon slots
	std::vector<std::unique_ptr<Weapon>> weapon_slots;

	std::unique_ptr<DebugUI> debuger;
	bool m_debug_on = false;

public:
	Game(const sf::Vector2u screen_resolver, 
		 const std::string& absolute_path);

	void run();

	~Game(){
		std::cout << "Destructor..." << std::endl;
		delete m_renderer;
		delete g_camera;
	}

private:

	void observe();

};


#endif // !ENGINE_H
