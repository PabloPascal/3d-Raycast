#ifndef ENEMY_H
#define ENEMY_H

#include "Thing.h"
#include "map.h"
#include <map>
#include "Player.h"
#include <SFML/Graphics.hpp>


class Enemy
{
public:

	virtual void update(const Player& player, const Map& map, float dt) = 0;

	virtual void attack() = 0;

	virtual void setTexture(textureID texture_id) = 0;
	virtual void setAIactivate(bool turn) = 0;

	virtual float getEnemySize() = 0;
	virtual float getSpeed() = 0;

	virtual void setAnimate(bool isAnimate) = 0;
	virtual void animation() = 0;
	virtual void set_animations(textureID tex_id) = 0;

};



#endif 