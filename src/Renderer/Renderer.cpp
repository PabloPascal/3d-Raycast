

#include "Renderer.h"
#include "Thing.h"
#include "Enemy.h"
#include "StaticObject.h"
#include "EntityManager.hpp"
#include "ResourceHolder.h"
#include "raycast.h"

#include <cmath>
#include <algorithm>
#include <iostream>
#include <array>
#include <thread>
#include <future>


#if NDEBUG
#define FLOOR_TEX 1
#else 
#define FLOOR_TEX 1
#endif



Renderer::Renderer(sf::RenderWindow& window) : 
	m_ScreenWidth(window.getSize().x), m_ScreenHeight(window.getSize().y), 
	m_pfloorPixels(nullptr), m_depth(15)
{
	m_window = &window;

	numThings = 0;
	m_wallVertexArray.setPrimitiveType(sf::Lines);
	m_roofVertexArray.setPrimitiveType(sf::Lines);
	m_floorVertexArray.setPrimitiveType(sf::Lines);
	//floor_buffer.setPrimitiveType(sf::Points);
	m_spriteColumnsVertexArray.setPrimitiveType(sf::Lines);
	zBuffer.resize(m_ScreenWidth);

	debugCollum.setPrimitiveType(sf::Lines);

	roofColor = sf::Color(100, 194, 255);

	//thread_pool = std::make_unique<ThreadPool>(NUM_THREADS);
	thread_pool = new ThreadPool(NUM_THREADS);
}


void Renderer::render(const Camera& camera, const wallSprite& wallSpriteInfo) {
	

	if (numThings != EntityManager::getInstance()->getVectorRenderables().size()) {

		numThings = EntityManager::getInstance()->getVectorRenderables().size();
		spriteOrder.resize(numThings);
		spriteDist.resize(numThings);
	}



	Ray ray;

	sf::Color shade;

	float wallHeight;
	float y_start_wall;
	float y_end_wall;

	m_wallVertexArray.resize(2 * m_ScreenWidth);
	m_roofVertexArray.resize(2 * m_ScreenWidth);
	

#if FLOOR_TEX == 0
	m_floorVertexArray.resize(2 * m_ScreenWidth);
#else
	m_pfloorPixels = new uint8_t[4 * m_ScreenWidth * m_ScreenHeight];

	
	//renderFloor(camera, 0, m_window.getSize().y);
	multithreadRenderFloor(camera);
	//threadPoolRenderFloor(camera);

	sf::Texture texture;
	sf::Image image;
	image.create(m_ScreenWidth, m_ScreenHeight, m_pfloorPixels);
	texture.loadFromImage(image);
	sf::Sprite floorSprite;
	floorSprite.setTexture(texture);

	m_window->draw(floorSprite);
#endif

	for (int x = 0; x < m_ScreenWidth; x++) {

		Ray ray = FastRayCast(camera, x, mapID::default_map, m_ScreenWidth, false);
		float distToWall = ray.dist;
		float delta_side = ray.delta_side;

		

		renderWall(x, distToWall, delta_side, camera, ray.wall_id, wallSpriteInfo);
		zBuffer[x] = distToWall;

	}
	// std::cout << "raycast()\n";


#if FLOOR_TEX == 0
	m_window->draw(m_floorVertexArray);
#endif


	m_window->draw(m_roofVertexArray);

	m_window->draw(m_wallVertexArray, &ResourceManager::getInstance()->getTexture(textureID::wallTexture));

	/*
	*   SPRITE RENDERING
	*/

	renderEntity(camera);


#if FLOOR_TEX == 0 
	m_floorVertexArray.clear();
#else
	delete[] m_pfloorPixels;
#endif
	m_roofVertexArray.clear();
	m_wallVertexArray.clear();


}





void Renderer::renderWall(int x, float distToWall, float delta_side,
						  const Camera& camera, int wall_id, 
						  const wallSprite& wallSpriteInfo) 
	{

	float textureWidth = wallSpriteInfo.texture_width;
	float textureHeight = wallSpriteInfo.texture_height;
	float offset = wallSpriteInfo.offset;
	sf::Color shade = shading(distToWall);

	int baseIndex = 2 * x;

	float wallHeight = (float)m_ScreenHeight / distToWall;
	float y_start_wall = (m_ScreenHeight - wallHeight) / 2 + camera.pitch + (camera.posZ / distToWall);
	float y_end_wall = (m_ScreenHeight + wallHeight) / 2 + camera.pitch + (camera.posZ / distToWall);;

	float texture_posX = delta_side * offset + offset * wall_id;


	/*
	* WALL
	*/
	m_wallVertexArray[baseIndex] = (sf::Vertex(sf::Vector2f(x, y_start_wall), shade, sf::Vector2f(texture_posX, 0)));
	m_wallVertexArray[baseIndex + 1] = (sf::Vertex(sf::Vector2f(x, y_end_wall), shade, sf::Vector2f(texture_posX, textureHeight)));

	/*
	* ROOOF
	*/
	m_roofVertexArray[baseIndex] = sf::Vertex(sf::Vector2f(x, 0), roofColor);
	m_roofVertexArray[baseIndex + 1] = sf::Vertex(sf::Vector2f(x, y_start_wall), roofColor);
	
	/*
	* FLOOR
	*/

#if FLOOR_TEX == 0 
	m_floorVertexArray[baseIndex] = (sf::Vertex(sf::Vector2f(x, y_end_wall), sf::Color::Black));
	m_floorVertexArray[baseIndex + 1] = (sf::Vertex(sf::Vector2f(x, m_ScreenHeight), sf::Color::White));
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





void Renderer::renderFloor(const Camera& camera,const size_t y_start,const size_t y_end) {


	float textureFloor_w = ResourceManager::getInstance()->getTexture(textureID::floor).getSize().x;
	float textureFloor_h = ResourceManager::getInstance()->getTexture(textureID::floor).getSize().y;

	for (int y = y_start; y < y_end; y++) {

		renderRowFloor(camera, y);

	}

}




void Renderer::multithreadRenderFloor(const Camera& camera){

	std::array<std::future<void>, NUM_THREADS> tasks;
	
	auto rowLoop = [&](size_t start, size_t end) {
		for (size_t i = start; i < end; i++) renderRowFloor(camera, i);
	};

	size_t numRowsPerTask = std::ceil((m_ScreenHeight) / NUM_THREADS);
	for (size_t i = 0; i < NUM_THREADS; i++) {
		size_t start = i * numRowsPerTask;
		size_t end = i == NUM_THREADS - 1 ? m_ScreenHeight : start + numRowsPerTask;
		tasks[i] = std::async(rowLoop, start, end);
	}


	for (size_t i = 0; i < NUM_THREADS; i++) {
		tasks[i].wait();
	}


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


void Renderer::renderEntity(const Camera& camera) {
	
	
	for (int i = 0; i < numThings; i++) {
		spriteOrder[i] = i;
		spriteDist[i] = std::pow(camera.m_position.x - EntityManager::getInstance()->getVectorRenderables()[i]->getPosition().x, 2) +
			std::pow(camera.m_position.y - EntityManager::getInstance()->getVectorRenderables()[i]->getPosition().y, 2);
	}

	spriteSort();
	for(int i : spriteOrder)
		renderPerSprite(camera, EntityManager::getInstance()->getVectorRenderables()[i]);


}




void Renderer::renderPerSprite(const Camera& camera, ThingPtr& thing) {

	sf::Vector2u textureSize = ResourceManager::getInstance()->getTexture(thing->getTextureID()).getSize();

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

	int ScreenX = int(m_ScreenWidth / 2.f * (1 + transform.x /transform.y));
	
	int spriteHeight = std::abs(int(m_ScreenHeight / transform.y ));

#define uDiv 1
#define vDiv 1
#define vMove 0.0

	int vMoveScreen = int(vMove / -transform.y) + camera.pitch + camera.posZ / -transform.y;


	float drawStartY = (float)m_ScreenHeight / 2 - (float)spriteHeight / 2 + vMoveScreen;
	float drawEndY = m_ScreenHeight / 2 + spriteHeight / 2 + vMoveScreen;

	int drawStartX = -spriteHeight / 2 + ScreenX;
	int drawEndX = spriteHeight / 2 + ScreenX;

	int startX = std::max((int)(drawStartX), 0);
	int endX = std::min((int)(drawEndX), (int)(m_ScreenWidth  - 1) );
	

	for (int x = startX; x < endX; x++) {
		//int t = x - textureSize.x / 2 + 1;
		
		if (transform.y < 0 && std::abs(transform.y) < zBuffer[x] && x > 0 && x < m_ScreenWidth) {

			float texCoordX = (x - (-spriteHeight / 2 + ScreenX)) * textureSize.y / spriteHeight;

			if(x == startX || x == endX - 1){
				debugCollum.append(sf::Vertex(sf::Vector2f(x, drawStartY), sf::Color::Green));
				debugCollum.append(sf::Vertex(sf::Vector2f(x, drawEndY), sf::Color::Green));
			}
			else{
				m_spriteColumnsVertexArray.append(sf::Vertex(sf::Vector2f(x, drawStartY), sf::Vector2f(texCoordX, 0)));
				m_spriteColumnsVertexArray.append(sf::Vertex(sf::Vector2f(x, drawEndY), sf::Vector2f(texCoordX, textureSize.y)));
			}
		}
	}



	m_window->draw(m_spriteColumnsVertexArray, &ResourceManager::getInstance()->getTexture(thing->getTextureID()));
	m_window->draw(debugCollum);

	m_spriteColumnsVertexArray.clear();
	debugCollum.clear();
}


void Renderer::renderRowFloor(const Camera& camera, const size_t y)
{
	float textureFloor_w = ResourceManager::getInstance()->getTexture(textureID::floor).getSize().x;
	float textureFloor_h = ResourceManager::getInstance()->getTexture(textureID::floor).getSize().y;

	sf::Vector2f rayDirLeft = camera.dir - camera.plane;
	sf::Vector2f rayDirRight = camera.dir + camera.plane;

	bool is_floor = y > m_ScreenHeight / 2 + camera.pitch;

	int p = is_floor ? (y - m_ScreenHeight / 2.f - camera.pitch) : (m_ScreenHeight / 2 - y + camera.pitch);

	float camZ = is_floor ? (0.5 * m_ScreenHeight + camera.posZ) : (0.5 * m_ScreenHeight - camera.posZ);

	float rowDistance = camZ / (float)p;

	sf::Vector2f floorStep = rowDistance * (rayDirLeft - rayDirRight) / (float)m_ScreenWidth;

	sf::Vector2f floorPos = camera.m_position + rowDistance * rayDirRight;


	if (is_floor) {
		for (int x = 0; x < m_ScreenWidth; x++) {

			sf::Vector2i cell(floorPos);

			sf::Vector2i texCoords = {
				(int)(textureFloor_w * (floorPos.x - cell.x)) & (int)(textureFloor_w - 1),
				(int)(textureFloor_h * (floorPos.y - cell.y)) & (int)(textureFloor_h - 1)
			};

			floorPos += floorStep;

			int index = 4 * (y * m_ScreenWidth + x);
			sf::Color color = ResourceManager::getInstance()->getImage(textureID::floor).getPixel(texCoords.x, texCoords.y);
			
			m_pfloorPixels[index + 0] = color.r;
			m_pfloorPixels[index + 1] = color.g;
			m_pfloorPixels[index + 2] = color.b;
			m_pfloorPixels[index + 3] = color.a;

		}//for x
	}//if



}


void Renderer::threadPoolRenderFloor(const Camera& camera)
{

	auto rowLoop = [&](size_t start, size_t end) {
		for (size_t i = start; i < end; i++) renderRowFloor(camera, i);
	};

	size_t numRowsPerTask = std::ceil((m_ScreenHeight) / NUM_THREADS);
	for (size_t i = 0; i < NUM_THREADS; i++) {
		
		size_t start = i * numRowsPerTask;
		size_t end = i == NUM_THREADS - 1 ? m_ScreenHeight : start + numRowsPerTask;

		thread_pool->add_task([=]{ rowLoop(start, end); });

	}




}
