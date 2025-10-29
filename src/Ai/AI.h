#ifndef AIAGENT_H
#define AIAGENT_H


#include "ResourceHolder.h"
#include <SFML/System/Vector2.hpp>
#include "PathFinder.h"
#include "Enemy.h"
#include "PathFinder.h"


class AI {
public:
	static PathFinder* pf;
	static bool inited;
public:
	AI() = default;

	static void init(const Map& map){
		pf = new PathFinder(map);
	}

	static void simpleEnemyAI(Enemy* enemy,Player& player,const Map& map, float dt);

	static void pathFindAlgorithm(Enemy* enemy, Player& player, const Map& map, float dt);

};

#endif