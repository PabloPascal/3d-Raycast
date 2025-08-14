#include "AI.h"
#include <cmath>



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


void AI::simpleEnemyAI(Enemy* enemy,const Player& player,const Map& map, float dt){
	RenderebleThing* ptr = dynamic_cast<RenderebleThing*>(enemy);

	sf::Vector2f direction = player.getCamera().m_position - ptr->getPosition();
	
	float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	//std::cout << "dist = " << dist << std::endl;
	direction /= dist;

	sf::Vector2f move = direction * enemy->getSpeed() * dt;
	sf::Vector2f newPos = ptr->getPosition() + move;

	float enemy_size = enemy->getEnemySize();
	float xOffset = move.x > 0 ? enemy_size / 2 : -enemy_size / 2;
	float yOffset = move.y > 0 ? enemy_size / 2 : -enemy_size / 2;

	if (ptr->getCollisionIndicate()) {

		if (PhysicsEngine::checkEnemyMapCollision(map, {newPos.x + xOffset, ptr->getPosition().y}, enemy_size, false)) 
		{
			ptr->setPosition({newPos.x, ptr->getPosition().y});

		}
		if(PhysicsEngine::checkEnemyMapCollision(map, {ptr->getPosition().x, newPos.y + yOffset}, enemy_size, true)) {
			
			ptr->setPosition({ ptr->getPosition().x, newPos.y});

		}

	}else{
		ptr->setPosition(newPos);
	}


}