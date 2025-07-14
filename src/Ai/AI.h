#pragma once
#include "ResourceHolder.h"
#include <SFML/System/Vector2.hpp>
#include "PathFinder.h"
#include "Enemy.h"


class AI {
public:
	
public:
	AI() = default;
	static sf::Vector2f simpleAI(const sf::Vector2f& enemyPos,const sf::Vector2f& playerPos, float dt);

	static void pathFindAlgorithm(sf::Vector2f& EnemyPosition, float enemy_speed, sf::Vector2f playerPos, float dt);

};