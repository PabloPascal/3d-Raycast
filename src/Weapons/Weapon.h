#pragma once 
#include "defines.h"


class Weapon {
public:

	Weapon(textureID weapon_id);
	
	Weapon() = default;

	virtual void shoot();

	virtual textureID getTextureId() { return m_weaponTextureId; }

private:
	textureID m_weaponTextureId;
};