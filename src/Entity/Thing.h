#pragma once
#include <SFML/System/Vector2.hpp>

#include "defines.h"

enum class textureID;

class RenderebleThing 
{	

	sf::Vector2f m_position;

public:

	virtual sf::Vector2f getPosition() const = 0;
	virtual void setPosition(const sf::Vector2f& pos) = 0;
	virtual textureID getTextureID() const = 0;
	virtual void setTexture(textureID texture_id) = 0;
	virtual bool isAnimate() = 0;
	virtual bool getCollisionIndicate() = 0;
	virtual void setCollision(bool collision) = 0;
};
