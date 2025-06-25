#pragma once
#include "ResourceHolder.h"
#include "Player.h"



enum class textureID {
	wallbrick,
	floor,
	prigojinTexture,
	barrelTexture
};



class Renderer
{
protected:
	ResourceHolder<textureID, sf::Texture> mTextures;
	ResourceHolder<textureID, sf::Image> mImages;
	std::vector<Map> mMaps;
	std::vector<EnemyPtr> enemies;
	std::vector<ObjectPtr> objects;
	std::vector<ThingPtr> things;


	sf::RenderWindow m_window;

	size_t numThings;

	struct Ray {
		float dist;
		float delta_side;
	};

	float m_depth = 15;

public:

	Renderer(size_t width, size_t height);

	void render(const Camera& camera);

	void draw();
	
private:

	Ray FastRayCast(const Camera& camera, int x);

	void texturingFloor(const Camera& camera, size_t y_start, size_t y_end);

	void texturingFloorFast(const Camera& camera);

	void texturingSprite(const Camera& camera);
	
	void texturingPerSprite(const Camera& camera, ThingPtr thing);

	void multithreadingFloor();

	void spriteSort();

	sf::Color shading(float dist);

	void texturingWall(int x, float distToWall, float delta_side);

private:

	std::vector<float> zBuffer;
	std::vector<int> spriteOrder;
	std::vector<float> spriteDist;


	sf::VertexArray roof;
	sf::VertexArray wall;
	sf::VertexArray floor;
	sf::VertexArray floor_buffer;
	sf::VertexArray spriteColumns;
};