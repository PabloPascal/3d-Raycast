

#ifndef DEFINES
#define DEFINES 

#include <memory>


/*
				TEXTURE ID DEFINES
*/


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


/*

					MAP DEFINES 

*/


enum class mapID {
	default_map
};

/*

			ENTITY DEFINES 

*/



class Demon;
class Player;
class RenderableThing;
class Enemy;
class StaticObject;


enum class EnemyType{
	Demon,
	Eye,
};

enum class StaticObjectType{
	pillar, 

};



/*

			PTR DEFINES 

*/

using EnemyPtr = std::shared_ptr<Enemy>;
using ObjectPtr = std::shared_ptr<StaticObject>;
using ThingPtr = std::shared_ptr<RenderableThing>;


/*

		WALL SPRITE 

*/

struct wallSprite{

	textureID m_id;

	size_t texture_width;
	size_t texture_height;
	unsigned short sprite_count;
	size_t offset;

};


struct Ray {
		float dist;
		float delta_side;
		int wall_id;
	};



/*

				SOUNDS DEFINES 

*/



enum class soundID{
	shotgun_fire_sound,
};



#endif 