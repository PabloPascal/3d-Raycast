#include "../headers/Physics.h"


bool PhysicsEngine::checkCollision(const Map& map, const sf::Vector2f& pos, const std::vector<sf::Sprite>& sprites){



	if(map.m_world[(int)pos.y][(int)pos.x] > 0){
	
		return false;
	
	}

	
	for(auto sprite: sprites){
		float dist = std::sqrt(std::pow((pos.x - sprite.getPosition().x), 2) +
			std::pow((pos.y - sprite.getPosition().y), 2));
		if (dist < 0.3) {
			return false;
		}

	}

	return true;


}