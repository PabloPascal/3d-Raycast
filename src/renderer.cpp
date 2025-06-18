#include "../headers/3dEngine.h"

#if NDEBUG
#define FLOOR_TEX 1
#else 
#define FLOOR_TEX 0
#endif



void Engine::render() {

	Ray ray;

	sf::Color shade;

	float wallHeight;
	float y_start_wall;
	float y_end_wall;

	int baseIndex = 0;

	wall.resize(2 * m_screen_width);
	roof.resize(2 * m_screen_width);
#if FLOOR_TEX == 0
	floor.resize(2 * m_screen_width);
#else
	buffer.resize(m_screen_width * m_screen_height / 2);
#endif

	/*float angle = m_player->getAngle();
	dir = { cos(angle),sin(angle)};
	plane = { sin(angle), -cos(angle)};*/


#if FLOOR_TEX
	texturingFloor();
#endif

	//#pragma omp parallel for
	for (int x = 0; x < m_screen_width; x++) {

		Ray ray = FastRayCast(x);
		float distToWall = ray.dist;
		float delta_side = ray.delta_side;

		//texturing_buffer(x, distToWall, delta_side, texture_block);
		texturingWall(x, distToWall, delta_side);

	}



}




Engine::Ray Engine::FastRayCast(int x) {

	float cameraX = 2 * (float)x / (float)(m_screen_width)-1; //-1 <= cameraX <= 1
	float perpendicualar_dist = 0;

	bool isHorizontal = false;

	sf::Vector2f pos = m_player->getPos();
	sf::Vector2f rayDir = dir - plane * cameraX;
	sf::Vector2f sideDist;
	sf::Vector2f deltaDist = { sqrt(1.0f + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
				sqrt(1.0f + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y)) };
	sf::Vector2i mapPos(pos);
	sf::Vector2f step;

	auto world = mMaps.m_world;


	if (rayDir.x < 0.0f) {
		step.x = -1;
		sideDist.x = (pos.x - mapPos.x) * deltaDist.x;
	}
	else {
		step.x = 1;
		sideDist.x = (mapPos.x + 1.0f - pos.x) * deltaDist.x;
	}
	if (rayDir.y < 0.0f) {
		step.y = -1;
		sideDist.y = (pos.y - mapPos.y) * deltaDist.y;
	}
	else {
		step.y = 1;
		sideDist.y = (mapPos.y + 1.0f - pos.y) * deltaDist.y;
	}

	while (world[mapPos.y][mapPos.x] == 0) {

		if (sideDist.x < sideDist.y) {
			sideDist.x += deltaDist.x;
			mapPos.x += step.x;
			isHorizontal = true;
			perpendicualar_dist = (mapPos.x - pos.x + (1 - step.x) / 2) / rayDir.x;
		}
		else {
			sideDist.y += deltaDist.y;
			mapPos.y += step.y;
			isHorizontal = false;
			perpendicualar_dist = (mapPos.y - pos.y + (1 - step.y) / 2) / rayDir.y;
		}


	}

	float wall_x;
	if (isHorizontal) {
		wall_x = pos.y + perpendicualar_dist * rayDir.y;
	}
	else {
		wall_x = pos.x + perpendicualar_dist * rayDir.x;
	}
	wall_x -= std::floor(wall_x);


	if (isHorizontal)
		return { perpendicualar_dist, wall_x };
	else
		return { perpendicualar_dist, wall_x };

}



void Engine::texturingWall(int x, float distToWall, float delta_side) {

	float texture_width = mTextures.get(textureID::wallbrick).getSize().x;

	sf::Color shade = shading(distToWall);

	int baseIndex = 2 * x;

	float wallHeight = (float)m_screen_height / distToWall;
	//float y_start_wall = (m_screen_height - wallHeight) / 2 - m_player->getVerticalAngle();
	//float y_end_wall = (m_screen_height + wallHeight) / 2 - m_player->getVerticalAngle();
	float y_start_wall = m_screen_height * 0.5 + -wallHeight * (1 - cameraHeight) - m_player->getVerticalAngle();;
	float y_end_wall = m_screen_height * 0.5 + wallHeight * cameraHeight - m_player->getVerticalAngle();

	float texture_pos = delta_side * texture_width;

	//wall
	wall[baseIndex] = (sf::Vertex(sf::Vector2f(x, y_start_wall), shade, sf::Vector2f(texture_pos, 0)));
	wall[baseIndex + 1] = (sf::Vertex(sf::Vector2f(x, y_end_wall), shade, sf::Vector2f(texture_pos, texture_width)));
	//std::cout << distToWall << std::endl;

	//roof
	roof[baseIndex] = (sf::Vertex(sf::Vector2f(x, 0), sf::Color(187, 211, 255)));
	roof[baseIndex + 1] = (sf::Vertex(sf::Vector2f(x, y_start_wall), sf::Color(187, 211, 255)));
	//floor
#if FLOOR_TEX == 0 
	floor[baseIndex] = (sf::Vertex(sf::Vector2f(x, y_end_wall), sf::Color::Black));
	floor[baseIndex + 1] = (sf::Vertex(sf::Vector2f(x, m_screen_height), sf::Color::White));
#endif

}



sf::Color Engine::shading(float dist) {

	sf::Color shade = sf::Color::White;
	if (dist >= m_depth - 1) {
		shade.a = 0.01;
		shade = sf::Color::Black;
	}

	if (dist > m_depth / 1.5) {
		shade.r /= 8;
		shade.g /= 8;
		shade.b /= 8;
	}
	if (dist < m_depth / 1.5 && dist > m_depth / 2.f) {
		shade.r /= 5;
		shade.g /= 5;
		shade.b /= 5;
	}
	if (dist < m_depth / 2.f && dist > m_depth / 2.5) {
		shade.r /= 3;
		shade.g /= 3;
		shade.b /= 3;
	}
	if (dist < m_depth / 2.5 && dist > m_depth / 3) {
		shade.r /= 2;
		shade.g /= 2;
		shade.b /= 2;
	}

	return shade;

}


#include <iostream>
void Engine::texturingFloor() {
	float textureFloor_w = mTextures.get(textureID::floor).getSize().x;
	float textureFloor_h = mTextures.get(textureID::floor).getSize().y;

	//#pragma omp parallel for
	for (int y = m_screen_height / 2 + 1; y < m_screen_height; y++) {

		sf::Vector2f rayDirLeft = dir - plane;
		sf::Vector2f rayDirRight = dir + plane;


		int p = y - m_screen_height / 2.f;
		float posZ = 0.5 * m_screen_height;

		float rowDistance = posZ / (float)p;
		sf::Vector2f floorStep = rowDistance * (rayDirLeft - rayDirRight) / (float)m_screen_width;

		sf::Vector2f floorPos = m_player->getPos() + rowDistance * rayDirRight;



		for (int x = 0; x < m_screen_width; x++) {

			sf::Vector2i cell(floorPos);

			sf::Vector2i texCoords = {
				(int)(textureFloor_w * (floorPos.x - cell.x)) & (int)(textureFloor_w - 1),
				(int)(textureFloor_h * (floorPos.y - cell.y)) & (int)(textureFloor_h - 1)
			};

			floorPos += floorStep;

			int index = (y - m_screen_height / 2.f) * m_screen_width + x;
			buffer[index] = sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(texCoords));

		}

	}

}