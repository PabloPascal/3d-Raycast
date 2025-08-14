#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>
#include <vector>
#include <memory>

#include "map.h"
#include "Renderer.h"
#include "AI.h" 
#include "shotgun.hpp"



class Game : public Renderer
{

	std::unique_ptr<Player> m_player;

	std::vector<EnemyPtr> enemies;
	std::vector<ObjectPtr> static_objects;

	sf::Sprite weaponSprite;
	sf::Sprite aim;

	std::unique_ptr<Weapon> weapon;

public:
	Game(const size_t screen_width, const size_t screen_height, 
		 const std::string& absolute_path);

	void run();


};


#endif // !ENGINE_H
