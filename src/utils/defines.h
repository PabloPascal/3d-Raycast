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
	aim
};



enum class mapID {
	default_map
};


class Thing;
class Enemy;
class Object;

using EnemyPtr = std::shared_ptr<Enemy>;
using ObjectPtr = std::shared_ptr<Object>;
using ThingPtr = std::shared_ptr<Thing>;



struct wallSprite{

	textureID m_id;

	size_t texture_width;
	size_t texture_height;
	unsigned short sprite_count;
	size_t offset;

};

