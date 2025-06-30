#pragma once
#include <SFML/Graphics.hpp>

enum class textureID {
	wallbrick,
	floor,
	prigojinTexture,
	barrelTexture,
	pillar,
	light
};


class Thing 
{	

public:
	Thing() = default;
	virtual sf::Vector2f getPosition() = 0;
	virtual void setPosition(const sf::Vector2f& pos) = 0;
	virtual textureID getTextureID() = 0;
	virtual bool isAnimate() = 0;
	virtual bool getCollisionIndicate() = 0;
};
