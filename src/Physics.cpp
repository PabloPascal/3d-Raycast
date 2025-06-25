#include "../headers/Physics.h"


bool PhysicsEngine::checkCollision(const Map& map, const sf::Vector2f& pos, const std::vector<ThingPtr>& things){



	if(map.m_world[(int)pos.y][(int)pos.x] > 0){
	
		return false;
	
	}

	
	/*for(const auto& thing: things){
		float dist = std::sqrt(std::pow((pos.x - thing->getPosition().x), 2) +
			std::pow((pos.y - thing->getPosition().y), 2));
		if (dist < 0.3) {
			return false;
		}

	}*/

	return true;


}