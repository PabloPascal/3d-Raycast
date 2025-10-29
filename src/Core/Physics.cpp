#include "Physics.h"
#include <iostream>
#include <cmath>

/*
		FALSE MEANS COLLISION! 
*/


#define COLLISION false
#define NOT_COLLISION true


bool PhysicsEngine::checkPlayerMapCollision(const Map& map, const sf::Vector2f& pos){



	if(map.m_world[(int)pos.y][(int)pos.x] > 0){
	
		return COLLISION;
	
	}

	return NOT_COLLISION;


}



bool PhysicsEngine::checkEnemyMapCollision(const Map& map, const sf::Vector2f& newEnemyPos, 
	float enemySize, bool isAxis) {
	int cell;

	sf::Vector2f size = {enemySize/2.f, enemySize/2.f};
	sf::Vector2f start = newEnemyPos - size;
	sf::Vector2f end = newEnemyPos + size;

	
	if(isAxis){
		for(int y = start.y; y < end.y; y++){
			
			//cell = map.getMapCell(newEnemyPos.x, y);
			cell = map.getMapCell(y, newEnemyPos.x);


			if(cell) {
				//std::cout << "y: " << y << std::endl;
				return COLLISION;
			}
		}

	}
	else{ 

		for(int x = start.x; x < end.x; x++){

			cell = map.getMapCell(newEnemyPos.y, x);

			if(cell){ 
				//std::cout << "x: " << x << std::endl;
				return COLLISION;
			}
		}

	}
	return NOT_COLLISION;

}



sf::Vector2f PhysicsEngine::findNormal(const sf::Vector2f& EntityPos, const sf::Vector2f& blockPos) {
	std::cout << "EntityPos: " << "(" << EntityPos.x << ", " << EntityPos.y << ")" << std::endl;
	std::cout << "blockPos: " << "(" << blockPos.x << ", " << blockPos.y << ")" << std::endl;

	if (EntityPos.x > blockPos.x - 0.5f && EntityPos.x < blockPos.x + 0.5f) {

		if (EntityPos.y - blockPos.y + 0.5 >= 0) return { 0, 1 };
		else return { 0, -1 };
	}

	if (EntityPos.y > blockPos.y - 0.5f && EntityPos.y < blockPos.y + 0.5f) {
		if (EntityPos.x - blockPos.x > 0) return { 1,0 };
		else return { -1,0 };

	}

	return {0,0};
}


void PhysicsEngine::PlayerCollisionReact(const sf::Vector2f& direction, sf::Vector2f& position ,const Map& map, float playerSpeed, float playerSize,
	const std::vector<ThingPtr>& things, sf::RenderWindow& window, float dt) {

	if (direction.x > 0 && PhysicsEngine::checkPlayerMapCollision(map, { position.x + playerSpeed * direction.x * dt + playerSize, position.y })) {
		position.x += playerSpeed * direction.x * dt;
	}
	if (direction.x < 0 && PhysicsEngine::checkPlayerMapCollision(map, { position.x + playerSpeed * direction.x * dt - playerSize, position.y })) {
		position.x += playerSpeed * direction.x * dt;
	}

	if (direction.y > 0 && PhysicsEngine::checkPlayerMapCollision(map, { position.x, position.y + playerSpeed * direction.y * dt + playerSize })) {
		position.y += playerSpeed * direction.y * dt;
	}

	if (direction.y < 0 && PhysicsEngine::checkPlayerMapCollision(map, { position.x, position.y + playerSpeed * direction.y * dt - playerSize })) {
		position.y += playerSpeed * direction.y * dt;
	}



}



void PhysicsEngine::EnemyCollisionResolver(Enemy* enemy, const Map& map, sf::Vector2f delta)
{

		float speed = enemy->getSpeed();

	if(myMATH::scalarProd(delta, sf::Vector2f(0,1)) > 0){

        if(map( (enemy->getPosition() + delta).y + 0.5, enemy->getPosition().x) == 0)
            {
                enemy->setPosition({enemy->getPosition().x,  (enemy->getPosition() + delta).y});
            }

        }
    if(myMATH::scalarProd(delta, sf::Vector2f(0,1)) < 0){

            if(map( (enemy->getPosition() + delta).y  - 0.5, enemy->getPosition().x ) == 0)
            {
                enemy->setPosition({enemy->getPosition().x,  (enemy->getPosition() + delta).y});
            }

        }

    if(myMATH::scalarProd(delta, sf::Vector2f(1,0)) > 0){

        if(map( enemy->getPosition().y , (enemy->getPosition() + delta).x + 0.5) == 0)
            {
                enemy->setPosition({(enemy->getPosition() + delta).x, enemy->getPosition().y});
        	}
    }
        if(myMATH::scalarProd(delta, sf::Vector2f(1,0)) < 0){
            if(map( enemy->getPosition().y, (enemy->getPosition() + delta).x  - 0.5) == 0)
            {
                enemy->setPosition({(enemy->getPosition() + delta).x, enemy->getPosition().y});
            }
        }
        
}