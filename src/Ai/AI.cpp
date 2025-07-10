#include "AI.h"


void AI::simpleAI(std::shared_ptr<Enemy>& enemy, sf::Vector2f playerPos, float dt){

	sf::Vector2f direction = playerPos - enemy->getPosition();
	
	float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= dist;

	enemy->setPosition(enemy->getPosition() + enemy->getSpeed() * dt * direction);

}


void AI::pathFindAlgorithm(sf::Vector2f& enemyPos, float enemy_speed, sf::Vector2f playerPos, float dt) {

	/*Node start = { static_cast<int>(enemyPos.x), static_cast<int>(enemyPos.y)};
	Node end = { static_cast<int>(playerPos.x), static_cast<int>(playerPos.y)};
	std::vector<Node> result = pathFinder->getPath(start, end);*/



}
