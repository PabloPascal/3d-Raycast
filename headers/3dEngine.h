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
	float m_depth = 25;

	sf::RenderWindow m_window;

	std::map<std::string, map> MAPS;
	std::string map_name;

	struct Ray{
		float dist;
		float delta_side;
	};

	std::unique_ptr<Player> m_player;
	sf::Texture m_texture;

	sf::VertexArray line;

public:
	Engine(int ScreenWidth, int ScreenHeight, float fov, sf::Vector2f start_pos, float start_angle = 0.f);

	void run();

	void add_map(std::string map_Name, map MAP);

	void changeMapName(std::string name);

private:

	Ray RayCast(int x);

	void render();

	bool collision(sf::Vector2f delta);

	void contol(float dt);

	sf::Color shading(float dist);
};


#endif // !ENGINE_H
