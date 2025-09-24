#ifndef WEAPON_H
#define WEAPON_H

#include "defines.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Weapon {
public:

	virtual void update(float dt) = 0;
	virtual void shoot() = 0;
	virtual void shoot(Camera* camera) = 0;
	virtual void animating() = 0;
	virtual textureID getTextureId() const = 0;
    virtual void load_animation(textureID animation_id) = 0;
	virtual soundID getSoundID() = 0;
	virtual bool getShootIndicate() = 0;
	virtual void setCooldownTime(float time_as_millisec) = 0;
	virtual void draw(sf::RenderWindow&) = 0; 
};



#endif