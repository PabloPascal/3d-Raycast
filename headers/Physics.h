#pragma once
#include "Map.h"
#include <SFML/Graphics.hpp>

class PhysicsEngine {


public:

	PhysicsEngine() = default;

	static bool checkCollision(const Map& map,const sf::Vector2f& pos,const std::vector<sf::Sprite>& sprites);


};

