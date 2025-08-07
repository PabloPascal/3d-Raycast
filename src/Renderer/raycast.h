#pragma once 


struct Ray {
	float dist;
	float delta_side;
	int wall_id;
};


Ray FastRayCast(const Camera& camera, int x, mapID map_id);


