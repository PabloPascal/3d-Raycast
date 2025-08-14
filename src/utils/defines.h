#pragma once
#include <memory>

enum class textureID {
	wallTexture,
	floor,
	prigojinTexture,
	barrelTexture,
	pillar,
	light,
	weapon,
	aim,
	monster_run1,
	monster_run2,
	monster_run3,
	weapon_fire1,
	weapon_fire2,
	weapon_fire3
};



enum class mapID {
	default_map
};


class Demon;
class Player;
class RenderebleThing;
class Enemy;
class StaticObject;

using EnemyPtr = std::shared_ptr<Enemy>;
using ObjectPtr = std::shared_ptr<StaticObject>;
using ThingPtr = std::shared_ptr<RenderebleThing>;



struct wallSprite{

	textureID m_id;

	size_t texture_width;
	size_t texture_height;
	unsigned short sprite_count;
	size_t offset;

};

