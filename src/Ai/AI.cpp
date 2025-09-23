#include "AI.h"
#include <cmath>
#include "MathLib.h"


sf::Vector2f AI::simpleAI(const sf::Vector2f& enemyPos,const sf::Vector2f& playerPos, float dt){

	sf::Vector2f direction = playerPos - enemyPos;
	
	float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	//std::cout << "dist = " << dist << std::endl;
	direction /= dist;

	return direction;

}


void AI::pathFindAlgorithm(sf::Vector2f& enemyPos, float enemy_speed,sf::Vector2f playerPos, float dt) {

	/*Node start = { static_cast<int>(enemyPos.x), static_cast<int>(enemyPos.y)};
	Node end = { static_cast<int>(playerPos.x), static_cast<int>(playerPos.y)};
	std::vector<Node> result = pathFinder->getPath(start, end);*/



}


void AI::simpleEnemyAI(Enemy* enemy,Player& player,const Map& map, float dt){

	sf::Vector2f direction = player.getCamera()->m_position - enemy->getPosition();
	
	float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	//std::cout << "dist = " << dist << std::endl;
	direction /= dist;

	sf::Vector2f move = direction * enemy->getSpeed() * dt;
	sf::Vector2f newPos = enemy->getPosition() + move;

	float enemy_size = enemy->getSize();
	float xOffset = move.x > 0 ? enemy_size / 2 : -enemy_size / 2;
	float yOffset = move.y > 0 ? enemy_size / 2 : -enemy_size / 2;

	if (enemy->getCollisionIndicate()) {

		if (PhysicsEngine::checkEnemyMapCollision(map, {newPos.x + xOffset, enemy->getPosition().y}, enemy_size, false)) 
		{
			enemy->setPosition({newPos.x, enemy->getPosition().y});

		}
		if(PhysicsEngine::checkEnemyMapCollision(map, {enemy->getPosition().x, newPos.y + yOffset}, enemy_size, true)) {
			
			enemy->setPosition({ enemy->getPosition().x, newPos.y});

		}

	}else{
		enemy->setPosition(newPos);
	}

	if(myMATH::VectorLen(enemy->getPosition() - player.getCamera()->m_position) < 1){
		enemy->attack(player);
	}


}