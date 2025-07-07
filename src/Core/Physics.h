#pragma once
#include "ResourceHolder.h"



class PhysicsEngine {


public:

	PhysicsEngine() = default;

	static bool checkCollision(const Map& map,const sf::Vector2f& pos, const std::vector<ThingPtr>& things);

};

