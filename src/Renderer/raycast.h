#ifndef RAYCAST_H
#define RAYCAST_H

#include "Player.h"
#include "Thing.h"

struct Ray {
		float dist;
		float delta_side;
		int wall_id;

        Enemy* hitted_thing = nullptr; 

	};


Ray FastRayCast(const Camera& camera, int x, mapID map_id, size_t screen_width, bool checkThings);



#endif