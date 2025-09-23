#include "raycast.h"
#include "defines.h"
#include "map.h"
#include "ResourceHolder.h"
#include "EntityManager.hpp"
#include "MathLib.h"

#include <SFML/System/Vector2.hpp>
#include <cmath>



Ray FastRayCast(const Camera& camera, int x, mapID map_id, size_t screen_width, bool checkThings) {

    ResourceManager* 	inst_ptr = ResourceManager::getInstance();
	EntityManager* 		entity_ptr = EntityManager::getInstance();

	float cameraX = 2 * (float)x / (float)(screen_width)-1; //-1 <= cameraX <= 1
	float perpendicualar_dist = 0;
	float epsilon = 0.5;

	auto world = inst_ptr->getMap(map_id).m_world;

	bool isHorizontal = false;

	sf::Vector2f rayDir = camera.dir - camera.plane * cameraX;
	sf::Vector2f sideDist;
	sf::Vector2f deltaDist = { std::sqrt(1.0f + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
				std::sqrt(1.0f + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y)) };
	sf::Vector2i mapPos(camera.m_position);
	sf::Vector2f step;


	Enemy* hitEnemy = nullptr;


	if (rayDir.x < 0.0f) {
		step.x = -1;
		sideDist.x = (camera.m_position.x - mapPos.x) * deltaDist.x;
	}
	else {
		step.x = 1;
		sideDist.x = (mapPos.x + 1.0f - camera.m_position.x) * deltaDist.x;
	}
	if (rayDir.y < 0.0f) {
		step.y = -1;
		sideDist.y = (camera.m_position.y - mapPos.y) * deltaDist.y;
	}
	else {
		step.y = 1;
		sideDist.y = (mapPos.y + 1.0f - camera.m_position.y) * deltaDist.y;
	}

	while (world[mapPos.y][mapPos.x] == 0) {

		if (sideDist.x < sideDist.y) {
			sideDist.x += deltaDist.x;
			mapPos.x += step.x;
			isHorizontal = true;
			perpendicualar_dist = (mapPos.x - camera.m_position.x + (1 - step.x) / 2) / rayDir.x;
		}
		else {
			sideDist.y += deltaDist.y;
			mapPos.y += step.y;
			isHorizontal = false;
			perpendicualar_dist = (mapPos.y - camera.m_position.y + (1 - step.y) / 2) / rayDir.y;
		}

		if(checkThings){

			for(auto& thing : entity_ptr->getVectorEnemies()){
			
				float size = thing->getSize();

				if(mapPos == sf::Vector2i(thing->getPosition())){
					hitEnemy = thing.get();
					checkThings = false;
				}

			}



		}
	}


	int id = world[mapPos.x][mapPos.y];

	float wall_x;
	if (isHorizontal) {
		wall_x = camera.m_position.y + perpendicualar_dist * rayDir.y;
	}
	else {
		wall_x = camera.m_position.x + perpendicualar_dist * rayDir.x;
	}
	wall_x -= std::floor(wall_x);


	if (isHorizontal)
		return { perpendicualar_dist, wall_x, id, hitEnemy};
	else
		return { perpendicualar_dist, wall_x, id, hitEnemy};

}