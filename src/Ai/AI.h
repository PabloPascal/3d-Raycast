#pragma once
#include "ResourceHolder.h"
#include "PathFinder.h"


class AI {
public:

	static PathFinder* pathFinder;
	
public:
	AI() = default;
	static void simpleAI(sf::Vector2f& EnemyPosition,float enemy_speed, sf::Vector2f playerPos, float dt);

	static void pathFindAlgorithm(sf::Vector2f& EnemyPosition, float enemy_speed, sf::Vector2f playerPos, float dt);

};