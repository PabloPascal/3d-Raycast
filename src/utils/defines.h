

#ifndef DEFINES
#define DEFINES 

#include <memory>
#include <SFML/System/Vector2.hpp>


/*
				CAMERA
*/

struct Camera {
	[[maybe_unused]] float m_angle = 0;//angle with OX
	[[maybe_unused]] float m_fov = 0; //unused

	sf::Vector2f dir   = 	{ 1, 0 };
	sf::Vector2f plane = 	{ 0, 0.66 };
	sf::Vector2f m_position;

	float posZ = 0;
	float pitch = 0;


};


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

	aim,

	monster_run1,
	monster_run2,
	monster_run3,
	
	monster_death1,
	monster_death2,
	monster_death3,
	monster_death4,
	monster_death5,
	monster_death6,

	monser_attack1,
	monser_attack2,
	monser_attack3,


	weapon,
	weapon_fire1,
	weapon_fire2,
	weapon_fire3,

	pistol_0,
	pistol_1,
	pistol_2,
	pistol_3
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



/*

				SOUNDS DEFINES 

*/



enum class soundID{
	shotgun_fire_sound,
	pistol_frie_sound,
	monster_sound_attack,
	monster_sound_death,
	monster_sound,
	monster_pain,
	no_bullet_sound
};



#endif 