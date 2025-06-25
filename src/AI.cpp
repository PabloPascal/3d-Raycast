#include "../headers/AI.h"


void AI::simpleAI(const EnemyPtr& enemy, sf::Vector2f playerPos, float dt){

	sf::Vector2f direction = playerPos - enemy->getPosition();
	
	float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= dist;

	enemy->setPosition(enemy->getPosition() + enemy->getSpeed() * dt * direction);

}
