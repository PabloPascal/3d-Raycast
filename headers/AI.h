#pragma once
#include "Enemy.h"
#include "ResourceHolder.h"

class AI {


public:
	AI() = default;
	static void simpleAI(const EnemyPtr& enemy, sf::Vector2f playerPos, float dt);


};