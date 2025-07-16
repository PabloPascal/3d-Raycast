#include "AI.h"
#include <cmath>



sf::Vector2f AI::simpleAI(const sf::Vector2f& enemyPos,const sf::Vector2f& playerPos, float dt){

	sf::Vector2f direction = playerPos - enemyPos;
	
	float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= dist;

	return direction;

}


void AI::pathFindAlgorithm(sf::Vector2f& enemyPos, float enemy_speed,sf::Vector2f playerPos, float dt) {

	/*Node start = { static_cast<int>(enemyPos.x), static_cast<int>(enemyPos.y)};
	Node end = { static_cast<int>(playerPos.x), static_cast<int>(playerPos.y)};
	std::vector<Node> result = pathFinder->getPath(start, end);*/



}
