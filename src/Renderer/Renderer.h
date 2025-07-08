#pragma once
#include "ResourceHolder.h"
#include "Player.h"
#include "MathLib.h"
#include <thread>
#include <future>


#define NUM_THREADS 8


class Renderer
{
protected:
	ResourceHolder<textureID, sf::Texture> mTextures;
	ResourceHolder<textureID, sf::Image> mImages;
	
	Map mMap;
	std::vector<EnemyPtr> enemies;
	std::vector<ObjectPtr> objects;
	std::vector<ThingPtr> things;

	sf::RenderWindow m_window;

	size_t numThings;

	struct Ray {
		float dist;
		float delta_side;
		textureID wall_id;
	};

	float m_depth = 15;

public:

	Renderer(size_t width, size_t height);

	Renderer(const Renderer&) = delete;

	Renderer& operator=(const Renderer&) = delete;

	void render(const Camera& camera);
	
private:

	Ray FastRayCast(const Camera& camera, int x);

	void renderFloor(const Camera& camera, size_t y_start, size_t y_end);
	
	void renderRowFloor(const Camera& camera, size_t y);


	void renderSprite(const Camera& camera);
	
	void renderPerSprite(const Camera& camera, ThingPtr thing);

	void multithreadRenderFloor(const Camera& camera);

	void spriteSort();

	sf::Color shading(float dist);

	void renderWall(int x, float distToWall, float delta_side,const Camera& camera);

private:

	std::vector<float> zBuffer;
	std::vector<int> spriteOrder;
	std::vector<float> spriteDist;


	sf::VertexArray roof;
	sf::VertexArray wall;
	sf::VertexArray floor;
	//sf::VertexArray floor_buffer;
	sf::VertexArray spriteColumns;

	uint8_t* floorPixels;


};