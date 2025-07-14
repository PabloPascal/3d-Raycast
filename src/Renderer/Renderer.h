#pragma once
#include "ResourceHolder.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "MathLib.h"
#include <thread>
#include <future>
#include "defines.h"

#define NUM_THREADS 8


class Renderer
{
protected:
	ResourceHolder<textureID, sf::Texture> mTextures;
	ResourceHolder<textureID, sf::Image> mImages;


	std::unordered_map<mapID ,Map> mMap;
	std::vector<EnemyPtr> enemies;
	std::vector<ObjectPtr> objects;
	std::vector<ThingPtr> things;

	wallSprite wallSpriteInfo;

	sf::RenderWindow m_window;

	size_t numThings;

	struct Ray {
		float dist;
		float delta_side;
		int wall_id;
	};

	size_t m_ScreenWidth;
	size_t m_ScreenHeight;

	float m_depth = 15;

public:

	Renderer(size_t width, size_t height);

	Renderer(const Renderer&) = delete;

	Renderer& operator=(const Renderer&) = delete;

	void render(const Camera& camera);
	
private:

	Ray FastRayCast(const Camera& camera, int x, mapID);

	void renderFloor(const Camera& camera, const size_t y_start,const size_t y_end);
	
	void renderRowFloor(const Camera& camera, const size_t y);

	void renderEntity(const Camera& camera);
	
	void renderPerSprite(const Camera& camera, ThingPtr& thing);

	void multithreadRenderFloor(const Camera& camera);

	void spriteSort();

	sf::Color shading(float dist);

	void renderWall(int x, float distToWall, float delta_side, const Camera& camera, int wall_id);

	void drawSprite(textureID sprite_id);


private:

	sf::Color roofColor;

	std::vector<float> zBuffer;
	std::vector<int> spriteOrder;
	std::vector<float> spriteDist;


	sf::VertexArray m_roofVertexArray;
	sf::VertexArray m_wallVertexArray;
	sf::VertexArray m_floorVertexArray;
	sf::VertexArray m_spriteColumnsVertexArray;

	uint8_t* m_pfloorPixels;


};