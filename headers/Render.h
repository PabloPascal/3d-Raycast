#pragma once
#include "ResourceHolder.h"
#include "Player.h"


class Renderer
{

	struct Ray {
		float dist;
		float delta_side;
	};

	float m_depth = 15;

	std::vector<float> zBuffer;
	std::vector<int> spriteOrder;
	std::vector<float> spriteDist;

	size_t numSprites;


	sf::VertexArray roof;
	sf::VertexArray wall;
	sf::VertexArray floor;
	sf::VertexArray floor_buffer;
	sf::VertexArray sprite_buffer;

public:

	Renderer();

	void render(const sf::Vector2u& windowSize,const Map& map, const Camera& camera,
		const sf::Texture& floorTexture, const sf::Texture& wallTexture, const sf::Texture& spriteTexture, const std::vector<sf::Sprite>& sprites);

	void draw(sf::RenderTarget& target, const sf::Texture& floorTexture, const sf::Texture& wallTexture, const sf::Texture& spriteTexture);

private:

	Ray FastRayCast(const sf::Vector2u& windowSize, const Map& map, const Camera& camera, int x);

	void texturingFloor(const sf::Vector2u& windowSize, const Camera& camera,const sf::Texture floorTexture, size_t y_start, size_t y_end);

	void texturingFloorFast(const sf::Vector2u& windowSize, const Camera& camera, const sf::Texture floorTexture);

	void texturingSprite(const std::vector<sf::Sprite>& sprites, const sf::Vector2u& windowSize, const Camera& camera,const sf::Texture& spriteTexture);

	void multithreadingFloor();

	void spriteSort();

	sf::Color shading(float dist);

	void texturingWall(const sf::Vector2u& windowSize, const sf::Texture& texture, int x, float distToWall, float delta_side);


};