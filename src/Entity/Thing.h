#ifndef THING_H
#define THING_H

#include <SFML/System/Vector2.hpp>

#include "defines.h"


class IRenderable 
{	

	sf::Vector2f m_position;

public:

	virtual sf::Vector2f getPosition() const = 0;
	virtual float getSize() = 0;
	virtual void setPosition(const sf::Vector2f& pos) = 0;
	virtual textureID getTextureID() const = 0;
	virtual void setTexture(textureID texture_id) = 0;
	virtual bool isAnimate() = 0;
	virtual bool getCollisionIndicate() = 0;
	virtual void setCollision(bool collision) = 0;
	virtual ~IRenderable(){}
};



#endif 