#pragma once 
#include "defines.h"


class Weapon {
public:

	virtual void update(float dt) = 0;
	virtual void shoot() = 0;
	virtual void animate() = 0;
	virtual textureID getTextureId() const = 0;
    virtual void load_animation(textureID animation_id) = 0;
};



