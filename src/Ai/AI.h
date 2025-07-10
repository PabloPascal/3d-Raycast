#pragma once
#include "ResourceHolder.h"
#include <SFML/System/Vector2.hpp>
#include "PathFinder.h"
#include "Enemy.h"


class AI {
public:
	
public:
	AI() = default;
	static void simpleAI(std::shared_ptr<Enemy>& enemy, sf::Vector2f playerPos, float dt);

	static void pathFindAlgorithm(sf::Vector2f& EnemyPosition, float enemy_speed, sf::Vector2f playerPos, float dt);

};