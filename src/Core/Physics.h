#pragma once
#include <SFML/System/Vector2.hpp>
#include "map.h"
#include "ResourceHolder.h"
#include "defines.h"
#include "Thing.h"
#include "Enemy.h"
#include "StaticObject.h"
#include "MathLib.h"

class PhysicsEngine {


public:

	PhysicsEngine() = default;

	static bool checkPlayerMapCollision(const Map& map,const sf::Vector2f& newPlayerPos);

	static bool checkEnemyMapCollision(const Map& map, const sf::Vector2f& newEnemyPos, sf::Vector2f& dir, float enemySize);

	static sf::Vector2f findNormal(const sf::Vector2f& EntityPos,const sf::Vector2f& blockPos);

	static void PlayerCollisionReact(const sf::Vector2f& direction, sf::Vector2f& position, const Map& map, float playerSpeed, float playerSize,
		const std::vector<ThingPtr>& things, sf::RenderWindow& window, float dt);


};

