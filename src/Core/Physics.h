#pragma once
#include <SFML/System/Vector2.hpp>
#include "map.h"
#include "ResourceHolder.h"
#include "defines.h"
#include "Thing.h"
#include "Enemy.h"
#include "StaticObject.h"


class PhysicsEngine {


public:

	PhysicsEngine() = default;

	static bool checkCollision(const Map& map,const sf::Vector2f& pos, const std::vector<ThingPtr>& things);

};

