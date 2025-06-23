#include "../headers/Render.h"
#include <cmath>
#include <thread>
#include <algorithm>

#if NDEBUG
#define FLOOR_TEX 1
#else 
#define FLOOR_TEX 1
#endif

#define MULTI_THREAD 0

#define NUM_THREAD 8


Renderer::Renderer() 
{
	numSprites = 0;
	wall.setPrimitiveType(sf::Lines);
	roof.setPrimitiveType(sf::Lines);
	floor.setPrimitiveType(sf::Lines);
	floor_buffer.setPrimitiveType(sf::Points);
	sprite_buffer.setPrimitiveType(sf::Lines);

}


void Renderer::render(const sf::Vector2u& windowSize,const Map& map, const Camera& camera,
	const sf::Texture& floorTexture, const sf::Texture& wallTexture,  const sf::Texture& spriteTexture,const std::vector<sf::Sprite>& sprites) {
	
	if (numSprites != sprites.size()) {
		numSprites = sprites.size();

		spriteOrder.resize(numSprites);
		spriteDist.resize(numSprites);

	}

	Ray ray;

	sf::Color shade;

	float wallHeight;
	float y_start_wall;
	float y_end_wall;

	wall.resize(2 * windowSize.x);
	roof.resize(2 * windowSize.x);
	zBuffer.resize(windowSize.x);

#if FLOOR_TEX == 0
	floor.resize(2 * m_screen_width);
#else
	floor_buffer.resize(windowSize.x * windowSize.y / 2);
#endif
	
	texturingFloor(windowSize, camera, floorTexture, windowSize.y / 2 + 1, windowSize.y);

	for (int x = 0; x < windowSize.x; x++) {

		Ray ray = FastRayCast(windowSize, map, camera, x);
		float distToWall = ray.dist;
		float delta_side = ray.delta_side;

		texturingWall(windowSize, wallTexture, x, distToWall, delta_side);
		zBuffer[x] = distToWall;
	}

	//spire casting
	texturingSprite(sprites, windowSize, camera, spriteTexture);

}




Renderer::Ray Renderer::FastRayCast(const sf::Vector2u& windowSize, const Map& map,const Camera& camera, int x) {

	float cameraX = 2 * (float)x / (float)(windowSize.x)-1; //-1 <= cameraX <= 1
	float perpendicualar_dist = 0;


	auto world = map.m_world;

	bool isHorizontal = false;

	sf::Vector2f rayDir = camera.dir - camera.plane * cameraX;
	sf::Vector2f sideDist;
	sf::Vector2f deltaDist = { sqrt(1.0f + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
				sqrt(1.0f + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y)) };
	sf::Vector2i mapPos(camera.m_position);
	sf::Vector2f step;


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


	}

	float wall_x;
	if (isHorizontal) {
		wall_x = camera.m_position.y + perpendicualar_dist * rayDir.y;
	}
	else {
		wall_x = camera.m_position.x + perpendicualar_dist * rayDir.x;
	}
	wall_x -= std::floor(wall_x);


	if (isHorizontal)
		return { perpendicualar_dist, wall_x };
	else
		return { perpendicualar_dist, wall_x };

}

#include <iostream>

void Renderer::texturingWall(const sf::Vector2u& windowSize, const sf::Texture& texture,int x, float distToWall, float delta_side) {

	float texture_width =texture.getSize().x;

	sf::Color shade = shading(distToWall);

	int baseIndex = 2 * x;

	float wallHeight = (float)windowSize.y / distToWall;
	float y_start_wall = (windowSize.y - wallHeight) / 2;
	float y_end_wall = (windowSize.y + wallHeight) / 2;
	//float y_start_wall = windowSize.y * 0.5 + -wallHeight * (1 - 0.5 * windowSize.y);
	//float y_end_wall = windowSize.y * 0.5 + wallHeight * 0.5 * windowSize.y;

	//std::cout << "y_start_wall = " << y_start_wall << ", ";
	//std::cout << "y_end_wall = " << y_end_wall << std::endl;

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



sf::Color Renderer::shading(float dist) {

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


void Renderer::texturingFloor(const sf::Vector2u& windowSize, const Camera& camera, sf::Texture floorTexture,
	size_t y_start, size_t y_end) {


	float textureFloor_w = floorTexture.getSize().x;
	float textureFloor_h = floorTexture.getSize().y;


#if FLOOR_TEX
//#pragma omp parallel for
	for (int y = y_start; y < y_end; y++) {

		sf::Vector2f rayDirLeft = camera.dir - camera.plane;
		sf::Vector2f rayDirRight = camera.dir + camera.plane;


		int p = y - windowSize.y / 2.f;
		float posZ = 0.5 * windowSize.y;

		float rowDistance = posZ / (float)p;
		sf::Vector2f floorStep = rowDistance * (rayDirLeft - rayDirRight) / (float)windowSize.x;

		sf::Vector2f floorPos = camera.m_position + rowDistance * rayDirRight;



		for (int x = 0; x < windowSize.x; x++) {

			sf::Vector2i cell(floorPos);

			sf::Vector2i texCoords = {
				(int)(textureFloor_w * (floorPos.x - cell.x)) & (int)(textureFloor_w - 1),
				(int)(textureFloor_h * (floorPos.y - cell.y)) & (int)(textureFloor_h - 1)
			};

			floorPos += floorStep;

			int index = (y - windowSize.y / 2.f) * windowSize.x + x;
			floor_buffer[index] = sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(texCoords));
			

		}

	}
#endif
}




void Renderer::multithreadingFloor() {

}




void Renderer::spriteSort() {
	std::vector<std::pair<float, int>> spritesPair(numSprites);

	if (numSprites > 1) {
		for (int i = 0; i < numSprites; i++) {
			spritesPair[i] = std::make_pair(spriteDist[i], spriteOrder[i]);
		}

		std::sort(spritesPair.begin(), spritesPair.end());

		for (int i = 0; i < numSprites; i++) {
			spriteDist[i] = spritesPair[i].first;
			spriteOrder[i] = spritesPair[i].second;
		}
	}

}


float t = 0;
void Renderer::texturingSprite(const std::vector<sf::Sprite>& sprites, const sf::Vector2u& windowSize, const Camera& camera,const sf::Texture& spriteTexture) {
	t++;

	
	for (int i = 0; i < numSprites; i++) {
		spriteOrder[i] = i;
		spriteDist[i] = std::pow(camera.m_position.x - sprites[i].getPosition().x, 2) + std::pow(camera.m_position.y - sprites[i].getPosition().y, 2);
	}

	spriteSort();

	sf::Vector2u textureSize = spriteTexture.getSize();

	for (int i = 0; i < numSprites; i++) {

		sf::Vector2f spritePos = sprites[i].getPosition() - camera.m_position;

		/*
		[ planeX   dirX ] -1                                     [ dirY      -dirX ]
		[               ]     =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		[ planeY   dirY ]                                        [ -planeY  planeX ]
		*/

		float determ = 1.0f / (camera.plane.x * camera.dir.y - camera.dir.x * camera.plane.y);

		sf::Vector2f transform = { determ * (camera.dir.y * spritePos.x - camera.dir.x * spritePos.y),
								  determ * (camera.plane.y * spritePos.x - camera.plane.x * spritePos.y) };


		int ScreenX = (windowSize.x / 2) * (1 + transform.x / transform.y);


		float spriteSize = std::abs(windowSize.y / transform.y);
		
		int drawStartY = windowSize.y / 2 - spriteSize / 2;
		int drawEndY = windowSize.y / 2 + spriteSize / 2;

		drawStartY = std::max(drawStartY, 0);
		drawEndY = std::min(drawEndY, int(windowSize.y) - 1);

		int drawStartX = -spriteSize / 2 + ScreenX;
		int drawEndX = spriteSize / 2 + ScreenX;

		drawStartX = std::max(drawStartX, 0);
		drawEndX = std::min(drawEndX, (int)windowSize.x);

		//std::cout << "drawStartX = " << drawStartX << std::endl;
		//std::cout << "drawEndX = " << drawEndX << std::endl;
		//std::cout << drawStartY << std::endl;

		for (int x = drawStartX; x < drawEndX; x++) {
			if (-transform.y > 0 && std::abs(transform.y) < zBuffer[x]) {


				float texCoordX = int(256*(x - (-spriteSize/2 + ScreenX)) * textureSize.x / spriteSize) / 256;

				sprite_buffer.append(sf::Vertex(sf::Vector2f(x, drawStartY + 3 * sin(t / 20.f)), { texCoordX, 0 }));
				sprite_buffer.append(sf::Vertex(sf::Vector2f(x, drawEndY + 3 * sin(t / 20.f)), { texCoordX, (float)textureSize.y }));
			}
		}
	}
}



void Renderer::draw(sf::RenderTarget& target, const sf::Texture& floorTexture, const sf::Texture& wallTexture, const sf::Texture& spriteTexture) {

	target.clear();

	target.draw(floor_buffer, &floorTexture);
	target.draw(wall, &wallTexture);
	target.draw(roof);
	target.draw(sprite_buffer, &spriteTexture);
	

	floor_buffer.clear();
	wall.clear();
	sprite_buffer.clear();
}



void Renderer::texturingFloorFast(const sf::Vector2u& windowSize, const Camera& camera, const sf::Texture floorTexture) {


	float textureFloor_w = floorTexture.getSize().x;
	float textureFloor_h = floorTexture.getSize().y;

	//float wallHeight = (float)windowSize.y / distToWall;
	//int y_start = (windowSize.y + wallHeight) / 2;



#if FLOOR_TEX

	
	//#pragma omp parallel for
	/*for (int y = ; y < ; y++) {

		sf::Vector2f rayDirLeft = camera.dir - camera.plane;
		sf::Vector2f rayDirRight = camera.dir + camera.plane;


		int p = y - windowSize.y / 2.f;
		float posZ = 0.5 * windowSize.y;

		float rowDistance = posZ / (float)p;
		sf::Vector2f floorStep = rowDistance * (rayDirLeft - rayDirRight) / (float)windowSize.x;

		sf::Vector2f floorPos = camera.m_position + rowDistance * rayDirRight;



		for (int x = 0; x < windowSize.x; x++) {

			sf::Vector2i cell(floorPos);

			sf::Vector2i texCoords = {
				(int)(textureFloor_w * (floorPos.x - cell.x)) & (int)(textureFloor_w - 1),
				(int)(textureFloor_h * (floorPos.y - cell.y)) & (int)(textureFloor_h - 1)
			};

			floorPos += floorStep;

			int index = (y - windowSize.y / 2.f) * windowSize.x + x;
			floor_buffer[index] = sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(texCoords));


		}

	}*/
#endif



}