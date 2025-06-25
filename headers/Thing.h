#pragma once
#include <SFML/Graphics.hpp>



class Thing 
{	

public:
	Thing() = default;
	virtual sf::Vector2f getPosition() = 0;
	virtual void setPosition(const sf::Vector2f& pos) = 0;
	virtual sf::Image& getImage() = 0;
	virtual sf::Texture& getTexture() = 0;
	virtual bool isAnimate() = 0;
	virtual bool getCollisionIndicate() = 0;
};
