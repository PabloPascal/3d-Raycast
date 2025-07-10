#pragma once
#include <SFML/System/Vector2.hpp>

#include "defines.h"

enum class textureID;

class Thing 
{	

public:
	Thing() = default;
	virtual sf::Vector2f getPosition() const = 0;
	virtual void setPosition(const sf::Vector2f& pos) = 0;
	virtual textureID getTextureID() const = 0;
	virtual bool isAnimate() = 0;
	virtual bool getCollisionIndicate() = 0;
};
