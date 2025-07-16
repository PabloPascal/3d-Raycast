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



bool PhysicsEngine::checkEnemyMapCollision(const Map& map, const sf::Vector2f& newEnemyPos, sf::Vector2f& dir, float enemySize) {

	if (map.m_world[std::floor(newEnemyPos.x + enemySize)][std::floor(newEnemyPos.y)] > 0) {
		
		std::cout << "1 map[x][y] = " << map.m_world[std::floor(newEnemyPos.x + enemySize)][std::floor(newEnemyPos.y + enemySize)] << std::endl;
		
		dir = { enemySize, enemySize };
		return COLLISION;

	}
	if (map.m_world[std::floor(newEnemyPos.x - enemySize)][std::floor(newEnemyPos.y)] > 0) {
		
		std::cout << "2 map[x][y] = " << map.m_world[std::floor(newEnemyPos.x - enemySize)][std::floor(newEnemyPos.y - enemySize)] << std::endl;

		dir = { -enemySize, -enemySize };
		return COLLISION;

	}
	if (map.m_world[std::floor(newEnemyPos.x)][std::floor(newEnemyPos.y - enemySize)] > 0) {

		std::cout << "3 map[x][y] = " << map.m_world[std::floor(newEnemyPos.x + enemySize)][std::floor(newEnemyPos.y - enemySize)] << std::endl;

		dir = { enemySize, -enemySize };
		return COLLISION;

	}
	if (map.m_world[std::floor(newEnemyPos.x)][std::floor(newEnemyPos.y + enemySize)] > 0) {

		std::cout << "4 map[x][y] = " << map.m_world[std::floor(newEnemyPos.x - enemySize)][std::floor(newEnemyPos.y + enemySize)] << std::endl;

		dir = { -enemySize, enemySize };
		return COLLISION;

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