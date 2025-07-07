#include "Renderer.h"
#include <cmath>
#include <thread>
#include <algorithm>
#include <iostream>

#if NDEBUG
#define FLOOR_TEX 0
#else 
#define FLOOR_TEX 0
#endif



Renderer::Renderer(size_t width, size_t height) 
{
	m_window.create(sf::VideoMode(width, height), "RenderWindow");

	numThings = 0;
	wall.setPrimitiveType(sf::Lines);
	roof.setPrimitiveType(sf::Lines);
	floor.setPrimitiveType(sf::Lines);
	floor_buffer.setPrimitiveType(sf::Points);
	spriteColumns.setPrimitiveType(sf::Lines);

	//floor_buffer.resize(m_window.getSize().x * m_window.getSize().y);


	/*futures.resize(NUM_THREADS);
	threads.resize(NUM_THREADS);*/
}


void Renderer::render(const Camera& camera) {
	
	m_window.clear();


	if (numThings != things.size()) {

		things.reserve(numThings);
		std::copy(enemies.begin(), enemies.end(), std::back_inserter(things));
		std::copy(objects.begin(), objects.end(), std::back_inserter(things));

		spriteOrder.resize(numThings);
		spriteDist.resize(numThings);
	}


	Ray ray;

	sf::Color shade;

	float wallHeight;
	float y_start_wall;
	float y_end_wall;

	wall.resize(2 * m_window.getSize().x);
	roof.resize(2 * m_window.getSize().x);
	zBuffer.resize(m_window.getSize().x);


#if FLOOR_TEX == 0
	floor.resize(2 * m_window.getSize().x);
#else
	//renderFloor(camera, 0, m_window.getSize().y);
	//multithreadRenderFloor(camera);
	
#endif

	textureID texID;

	for (int x = 0; x < m_window.getSize().x; x++) {

		Ray ray = FastRayCast(camera, x);
		float distToWall = ray.dist;
		float delta_side = ray.delta_side;

		texID = ray.wall_id;

		renderWall(x, distToWall, delta_side, camera);
		zBuffer[x] = distToWall;

	}


#if FLOOR_TEX == 0
	m_window.draw(floor);
#endif
	//for (size_t i = 0; i < NUM_THREADS; i++) {
	//	futures[i].wait();
	//}

	m_window.draw(roof);
	m_window.draw(floor_buffer, &mTextures.get(textureID::floor));
	m_window.draw(wall, &mTextures.get(texID));

	//spire casting
	renderSprite(camera);


#if FLOOR_TEX == 0 
	floor.clear();
#else
	//floor_buffer.clear();
#endif
	roof.clear();
	wall.clear();


}




Renderer::Ray Renderer::FastRayCast(const Camera& camera, int x) {

	float cameraX = 2 * (float)x / (float)(m_window.getSize().x)-1; //-1 <= cameraX <= 1
	float perpendicualar_dist = 0;


	auto world = mMap.m_world;

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
		return { perpendicualar_dist, wall_x, textureID::wallGrayBrick};
	else
		return { perpendicualar_dist, wall_x, textureID::wallGrayBrick};

}




#include <iostream>
void Renderer::renderWall(int x, float distToWall, float delta_side, const Camera& camera) {

	float texture_width = mTextures.get(textureID::wallbrick).getSize().x;

	sf::Color shade = shading(distToWall);

	int baseIndex = 2 * x;

	float wallHeight = (float)m_window.getSize().y / distToWall;
	float y_start_wall = (m_window.getSize().y - wallHeight) / 2 + camera.pitch + (camera.posZ / distToWall);
	float y_end_wall = (m_window.getSize().y + wallHeight) / 2 + camera.pitch + (camera.posZ / distToWall);;

	float texture_pos = delta_side * texture_width;

	//wall
	wall[baseIndex] = (sf::Vertex(sf::Vector2f(x, y_start_wall), shade, sf::Vector2f(texture_pos, 0)));
	wall[baseIndex + 1] = (sf::Vertex(sf::Vector2f(x, y_end_wall), shade, sf::Vector2f(texture_pos, texture_width)));

	//roof
	roof[baseIndex] = (sf::Vertex(sf::Vector2f(x, 0), sf::Color(187, 211, 255)));
	roof[baseIndex + 1] = (sf::Vertex(sf::Vector2f(x, y_start_wall), sf::Color(187, 211, 255)));
	//floor
#if FLOOR_TEX == 0 
	floor[baseIndex] = (sf::Vertex(sf::Vector2f(x, y_end_wall), sf::Color::Black));
	floor[baseIndex + 1] = (sf::Vertex(sf::Vector2f(x, m_window.getSize().y), sf::Color::White));
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





void Renderer::renderFloor(const Camera& camera, size_t y_start, size_t y_end) {


	float textureFloor_w = mTextures.get(textureID::floor).getSize().x;
	float textureFloor_h = mTextures.get(textureID::floor).getSize().y;


//#pragma omp parallel for schedule(dynamic,1)
	for (int y = y_start; y < y_end; y++) {

		sf::Vector2f rayDirLeft = camera.dir - camera.plane;
		sf::Vector2f rayDirRight = camera.dir + camera.plane;

		bool is_floor = y > m_window.getSize().y / 2 + camera.pitch;


		//int p = y - m_window.getSize().y / 2.f;
		int p = is_floor ? (y - m_window.getSize().y / 2.f - camera.pitch) : (m_window.getSize().y / 2 - y + camera.pitch);

		//float camZ = 0.5 * m_window.getSize().y;
		float camZ = is_floor ? (0.5 * m_window.getSize().y + camera.posZ) : (0.5 * m_window.getSize().y - camera.posZ);

		float rowDistance =  camZ / (float)p;
		sf::Vector2f floorStep = rowDistance * (rayDirLeft - rayDirRight) / (float)m_window.getSize().x;

		sf::Vector2f floorPos = camera.m_position + rowDistance * rayDirRight;


		if (is_floor) {
			for (int x = 0; x < m_window.getSize().x; x++) {

				sf::Vector2i cell(floorPos);

				sf::Vector2i texCoords = {
					(int)(textureFloor_w * (floorPos.x - cell.x)) & (int)(textureFloor_w - 1),
					(int)(textureFloor_h * (floorPos.y - cell.y)) & (int)(textureFloor_h - 1)
				};

				floorPos += floorStep;

				int index = y * m_window.getSize().x + x;
				floor_buffer[index] = sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(texCoords));
				
			}//for x
		}//if
	}//for y

}




void Renderer::multithreadRenderFloor(const Camera& camera){

	size_t offset = std::ceil(m_window.getSize().y / NUM_THREADS);
	size_t remain = m_window.getSize().y % NUM_THREADS;
	

	size_t index;
	for (size_t i = 0; i < NUM_THREADS; i++) {
		index = i * offset;
		futures[i] = std::async([&camera, &index, &offset, this]{renderFloor(camera, index, index + offset); });
	}
	if (offset != 0) {
		std::async([&camera, &index, &offset,&remain, this] {renderFloor(camera, index + offset, index + offset + remain); });
	}

	/*for (size_t i = 0; i < NUM_THREADS; i++) {
		index = i * offset;
		threads[i] = std::thread([&camera, &index, &offset, this] {renderFloor(camera, index, index + offset); });
	}
	
	for (size_t i = 0; i < NUM_THREADS; i++) {
		threads[i].join();
	}*/



}




void Renderer::spriteSort() {
	std::vector<std::pair<float, int>> spritesPair(numThings);

	if (numThings > 1) {
		
		for (int i = 0; i < numThings; i++) {
			spritesPair[i] = std::make_pair(spriteDist[i], spriteOrder[i]);
		}

		std::sort(spritesPair.begin(), spritesPair.end(), std::greater<std::pair<int, float>>());

		for (int i = 0; i < numThings; i++) {
			spriteDist[i] = spritesPair[i].first;
			spriteOrder[i] = spritesPair[i].second;
		}
	}

}


void Renderer::renderSprite(const Camera& camera) {
	
	
	for (int i = 0; i < numThings; i++) {
		spriteOrder[i] = i;
		spriteDist[i] = std::pow(camera.m_position.x - things[i]->getPosition().x, 2) +
			std::pow(camera.m_position.y - things[i]->getPosition().y, 2);
	}

	spriteSort();
	for(int i : spriteOrder)
		renderPerSprite(camera, things[i]);


}




float t = 0;
void Renderer::renderPerSprite(const Camera& camera, ThingPtr thing) {
	t++;

	if (t > 1000) t -= 1000;

	sf::Vector2u textureSize = mTextures.get(thing->getTextureID()).getSize();

	sf::Vector2f spritePos = thing->getPosition() - camera.m_position;

	/*
	[ planeX   dirX ] -1                                     [ dirY      -dirX ]
	[               ]     =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	[ planeY   dirY ]                                        [ -planeY  planeX ]
	*/

	float inverse_determ = 1.0f / (camera.plane.x * camera.dir.y - camera.dir.x * camera.plane.y);
	sf::Vector2f transform = { inverse_determ * (camera.dir.y * spritePos.x - camera.dir.x * spritePos.y),
							  -inverse_determ* (-camera.plane.y * spritePos.x + camera.plane.x * spritePos.y) };


	if (transform.y > 0) {
		return;
	}

	int ScreenX = int(m_window.getSize().x / 2.f * (1 + transform.x /transform.y));
	
	int spriteSize = std::abs(int(m_window.getSize().y / transform.y ));

#define uDiv 1
#define vDiv 1
#define vMove 0.0

	int vMoveScreen = int(vMove / -transform.y) + camera.pitch + camera.posZ / -transform.y;


	float drawStartY = (float)m_window.getSize().y / 2 - (float)spriteSize / 2 + vMoveScreen;
	float drawEndY = m_window.getSize().y / 2 + spriteSize / 2 + vMoveScreen;

	int drawStartX = -spriteSize / 2 + ScreenX;
	int drawEndX = spriteSize / 2 + ScreenX;

	int startX = std::max(drawStartX, 0);
	int endX = std::min(drawEndX, (int)(m_window.getSize().x  - 1));
	
	for (int x = startX; x < endX ;  x++) {
		if (transform.y < 0 && std::abs(transform.y) < zBuffer[x] && x > 0 && x < m_window.getSize().x) {

			float texCoordX = (x - (-spriteSize / 2 + ScreenX)) * textureSize.y / spriteSize;

			spriteColumns.append(sf::Vertex(sf::Vector2f(x, drawStartY), sf::Vector2f(texCoordX, 0)));
			spriteColumns.append(sf::Vertex(sf::Vector2f(x, drawEndY), sf::Vector2f(texCoordX, textureSize.y)));

		}
	}


	m_window.draw(spriteColumns, &mTextures.get(thing->getTextureID()));

	spriteColumns.clear();

}



