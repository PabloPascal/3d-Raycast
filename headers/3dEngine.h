#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>
#include <vector>
#include <memory>

#include "../headers/map.h"
#include "../headers/Player.h";
#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>




enum class textureID{
	wallbrick,
	floor
};

enum class imageID {
	map1
};


class Engine {

	ResourceHolder<textureID, sf::Texture> mTextures;
	ResourceHolder<imageID, sf::Image> mImages;
	map mMaps;

	int m_screen_width;
	int m_screen_height;
	float m_depth = 15;

	int world_width;
	int world_height;

	float cameraHeight;

	sf::RenderWindow m_window;

	struct Ray{
		float dist;
		float delta_side;
	};

	std::unique_ptr<Player> m_player;

	sf::VertexArray roof;
	sf::VertexArray wall;
	sf::VertexArray floor;
	sf::VertexArray buffer;

	sf::Vector2f plane = {0, 0.66f};
	sf::Vector2f dir = {0.5f, 0.f};

public:
	Engine(int ScreenWidth, int ScreenHeight, float fov, sf::Vector2f start_pos, float start_angle = 0.f);

	void run();

	
	void loadMap(std::string path);
	void loadMap(map& Maps);
	void loadTexture(std::string path);
	void loadTexture();
	void loadImage(std::string path);
	void loadImage();

private:

	void EventProcess();

	Ray FastRayCast(int x);

	void render();

	void texturingFloor();

	bool collision(sf::Vector2f delta);

	void contol(float dt);

	void transformation_coords(float dt);

	sf::Color shading(float dist);

	void texturingWall(int x, float distToWall, float delta_side);
};


#endif // !ENGINE_H
