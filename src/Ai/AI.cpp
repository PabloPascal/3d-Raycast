#include "AI.h"

PathFinder* AI::pathFinder = nullptr;



void AI::simpleAI(sf::Vector2f& enemyPosition, float enemySpeed, sf::Vector2f playerPos, float dt){

	sf::Vector2f direction = playerPos - enemyPosition;
	
	float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= dist;

	enemyPosition = (enemyPosition + enemySpeed * dt * direction);

}


void AI::pathFindAlgorithm(sf::Vector2f& enemyPos, float enemy_speed, sf::Vector2f playerPos, float dt) {

	/*Node start = { static_cast<int>(enemyPos.x), static_cast<int>(enemyPos.y)};
	Node end = { static_cast<int>(playerPos.x), static_cast<int>(playerPos.y)};
	std::vector<Node> result = pathFinder->getPath(start, end);*/



}
