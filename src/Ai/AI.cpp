#include "AI.h"
#include <cmath>
#include "MathLib.h"


PathFinder* AI::pf = nullptr;
bool AI::inited = false;

sf::Vector2f AI::simpleAI(const sf::Vector2f& enemyPos,const sf::Vector2f& playerPos, float dt){

	sf::Vector2f direction = playerPos - enemyPos;
	
	float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	//std::cout << "dist = " << dist << std::endl;
	direction /= dist;

	return direction;

}


void AI::pathFindAlgorithm(Enemy* enemy, Player& player, const Map& map, float dt) {

	if(!inited){
		init(map);
		inited = true;
	}

	float speed = enemy->getSpeed();

	sf::Vector2i IenemyPos = {(int)(enemy->getPosition().x), (int)(enemy->getPosition().y)};
	sf::Vector2i IplayerPos = {(int)player.getPos().x, (int)player.getPos().y};

	Node start = {IenemyPos.y, IenemyPos.x};
	Node end = {IplayerPos.y, IplayerPos.x};

	std::vector<Node> path = AI::pf->getPath( start, end);
	
	int last = path.size() - 1;
	auto [x, y] = path[last];

	sf::Vector2f dir = sf::Vector2f((float)y + 0.5, (float)x + 0.5) - enemy->getPosition();


	if(myMATH::scalarProd(dir, sf::Vector2f(0,1)) > 0){

            if(map( (enemy->getPosition() + dir * speed*dt).y + 0.5, enemy->getPosition().x) == 0)
            {
                enemy->setPosition({enemy->getPosition().x,  (enemy->getPosition() + dir * speed*dt).y});
            }

        }
        if(myMATH::scalarProd(dir, sf::Vector2f(0,1)) < 0){

            if(map( (enemy->getPosition() + dir * speed*dt).y  - 0.5, enemy->getPosition().x ) == 0)
            {
                enemy->setPosition({enemy->getPosition().x,  (enemy->getPosition() + dir * speed*dt).y});
            }

        }

        if(myMATH::scalarProd(dir, sf::Vector2f(1,0)) > 0){
            if(map( enemy->getPosition().y , (enemy->getPosition() + dir * speed*dt).x + 0.5) == 0)
            {
                enemy->setPosition({(enemy->getPosition() + dir*speed*dt).x, enemy->getPosition().y});
            }
        }
        if(myMATH::scalarProd(dir, sf::Vector2f(1,0)) < 0){
            if(map( enemy->getPosition().y, (enemy->getPosition() + dir * speed*dt).x  - 0.5) == 0)
            {
                enemy->setPosition({(enemy->getPosition() + dir*speed*dt).x, enemy->getPosition().y});
            }
        }
        

	if(myMATH::VectorLen(enemy->getPosition() - player.getCamera()->m_position) < 1){
		enemy->attack(player);
	}


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

		if (PhysicsEngine::checkEnemyMapCollision(map, {enemy->getPosition().y, newPos.x + xOffset}, enemy_size, false)) 
		{
			enemy->setPosition({newPos.x, enemy->getPosition().y});

		}
		if(PhysicsEngine::checkEnemyMapCollision(map, {newPos.y + yOffset, enemy->getPosition().x}, enemy_size, true)) {
			
			enemy->setPosition({ enemy->getPosition().x, newPos.y});

		}

	}else{
		enemy->setPosition(newPos);
	}

	if(myMATH::VectorLen(enemy->getPosition() - player.getCamera()->m_position) < 1){
		enemy->attack(player);
	}


}