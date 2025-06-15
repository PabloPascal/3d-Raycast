#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>
#include <vector>
#include <memory>

#include "../headers/map.h"
#include "../headers/Player.h";

#include <SFML/Graphics.hpp>


class Engine {

	int m_screen_width;
	int m_screen_height;
	float m_depth = 15;

	sf::RenderWindow m_window;

	std::map<std::string, map> MAPS;
	std::string map_name;

	struct Ray{
		float dist;
		float delta_side;
	};

	std::unique_ptr<Player> m_player;
	sf::Texture m_texture_wall;
	sf::Texture m_texture_floor;

	sf::VertexArray roof;
	sf::VertexArray wall;
	sf::VertexArray floor;
	sf::VertexArray buffer;

	sf::Vector2f plane = {0, 0.66f};
	sf::Vector2f dir = {0.5f, 0.f};

public:
	Engine(int ScreenWidth, int ScreenHeight, float fov, sf::Vector2f start_pos, float start_angle = 0.f);

	void run();

	void add_map(std::string map_Name, map MAP);

	void changeMapName(std::string name);

private:

	void EventProcess();

	void handlePlayerInput(sf::Event, bool);

	Ray RayCast(int x);

	Ray FastRayCast(int x);

	void render();

	bool collision(sf::Vector2f delta);

	void contol(float dt);

	void transformation_coords(float dt);

	sf::Color shading(float dist);

	void texturing(int x, float distToWall, float delta_side, int texture_block);

	void texturing_buffer(int x, float distToWall, float delta_side, int texture_block);
};


#endif // !ENGINE_H
