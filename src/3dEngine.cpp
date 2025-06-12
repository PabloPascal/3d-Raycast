#include "../headers/3dEngine.h"

#include <omp.h>
#include <iostream>

Engine::Engine(int ScreenWidth, int ScreenHeight, float fov, sf::Vector2f start_pos, float start_angle) {

	m_screen_width = ScreenWidth;
	m_screen_height = ScreenHeight;

	m_window.create(sf::VideoMode(m_screen_width, m_screen_height), "3d");

	m_player = std::make_unique<Player>(fov, start_angle, start_pos);

	m_texture.loadFromFile("../res/walls.png");

	line.setPrimitiveType(sf::Lines);
}


void Engine::changeMapName(std::string name) {
	map_name = name;
}



Engine::Ray Engine::RayCast(int x) {

	float angle = m_player->getAngle();
	float Fov = m_player->getFov();
	sf::Vector2f pos = m_player->getPos();
	auto world = MAPS[map_name].m_world;
	int world_size_w = MAPS[map_name].size_x;
	int world_size_h = MAPS[map_name].size_y;

	float Ray_angle = (angle - Fov / 2) + (float)x / (float)m_screen_width * Fov;

	sf::Vector2f ray_dir = { cos(Ray_angle), sin(Ray_angle) };



	bool bHit = false;
	float dist = 0.f;
	float delta = 0.01;

	//distance from edge of grid
	float dx_side;
	float dy_side;

	sf::Vector2f ray = pos + sf::Vector2f{ dist * ray_dir.x, dist * ray_dir.y };
	sf::Vector2i test;

	bool isVertical = 0;

	while (bHit != true && dist < m_depth) {

		dist += delta;
		ray = pos + sf::Vector2f{ dist * ray_dir.x, dist * ray_dir.y };
		test.x = ray.x;
		test.y = ray.y;

		if (world[test.x][test.y] > 0) {

			bHit = true;

			isVertical = fabs(ray.x - std::round(ray.x)) < fabs(ray.y - std::round(ray.y));

		}

		if (test.x < 0 || test.x > world_size_w || test.y < 0 || test.y > world_size_h) {
			bHit = true;
			dist = m_depth;

			if (!isVertical) {
				dx_side = (pos.x + dist * ray_dir.x) - test.x;
				return { dist, dx_side };
			}
			else {
				dy_side = (pos.y + dist * ray_dir.y) - test.y;
				return { dist, dy_side };
			}
		}


	}

	//sf::Vector2f newP = (ray - pos);
	//float oldPx = newP.x;
	//newP.x = newP.x * cos(Ray_angle) - newP.y * sin(Ray_angle);
	//newP.y = oldPx * sin(Ray_angle) + newP.y * cos(Ray_angle);


	//float sqrtNewP = newP.x * newP.x + newP.y * newP.y;
	//float  prPx = newP.y;

	////std::cout << "prPx = " << prPx << std::endl;

	//if (prPx < 0.66 && prPx > 0) {
	//	dist = sqrt(sqrtNewP - prPx * prPx);
	//}

	if (!isVertical) {
		dx_side = (pos.x + dist * ray_dir.x) - test.x;
		return { dist, dx_side };
	}
	else {
		dy_side = (pos.y + dist * ray_dir.y) - test.y;
		return { dist, dy_side };
	}

}


void Engine::render(){

	Ray ray;
	int texture_block = m_texture.getSize().x / 8;
	sf::Color shade;

	line.resize(6 * m_screen_width);

	float wallHeight;
	float y_start_wall;
	float y_end_wall;
	float texture_pos;



//#pragma omp parallel for private(wallHeight, y_start_wall,y_end_wall,texture_pos)
	for (int x = 0; x < m_screen_width; x++) {
		
		Ray ray = RayCast(x);
		float distToWall = ray.dist;
		float delta_side = ray.delta_side;

		wallHeight  = 2 * (double)m_screen_height / distToWall;
		y_start_wall = (m_screen_height - wallHeight) / 2;
		y_end_wall =(m_screen_height + wallHeight) / 2;


		texture_pos = delta_side * texture_block;

		shade = shading(distToWall);

		int base_index = x * 6;
		//roof
		line[base_index] = (sf::Vertex(sf::Vector2f(x, 0), sf::Color::Black));
		line[base_index + 1] = (sf::Vertex(sf::Vector2f(x, y_start_wall), sf::Color::Black));
		//wall
		line[base_index + 2] = (sf::Vertex(sf::Vector2f(x, y_start_wall), shade, sf::Vector2f(128 + texture_pos, 0)));
		line[base_index + 3] = (sf::Vertex(sf::Vector2f(x, y_end_wall), shade, sf::Vector2f(128 + texture_pos, m_texture.getSize().y / 4)));
		//floor
		line[base_index + 4] = (sf::Vertex(sf::Vector2f(x, y_end_wall), sf::Color::Green));
		line[base_index + 5] = (sf::Vertex(sf::Vector2f(x, m_screen_height), sf::Color::Green));
		

	}
#pragma omp barrier
}



void Engine::add_map(std::string map_Name, map MAP) {

	map_name = map_Name;
	if (MAP.m_world.size() == 0) return;

	MAPS.insert(std::make_pair(map_Name, MAP));

}



void Engine::run() {

	float dt;
	sf::Clock clock;
	
	if (MAPS.size() == 0) {
		std::cerr << "no MAPs" << std::endl;
		return;
	}

	while (m_window.isOpen()) {

		dt = clock.restart().asSeconds();

		sf::Event event;
		while (m_window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) m_window.close();

		}


		render();
		
		contol(dt);

		m_window.clear();
		m_window.draw(line, &m_texture);
		m_window.display();
		line.clear();
		
	}

}

#include <iostream>

void Engine::contol(float dt) {

	float angle = m_player->getAngle();
	sf::Vector2f position = m_player->getPos();

	float speed_rot = 2 * dt;

	sf::Vector2f d_step = { 5 * dt * cos(angle), 5 * dt * sin(angle) };

	bool is_collision_x = false;
	bool is_collision_y = false;
	sf::Vector2f normal;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		angle -= speed_rot;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle += speed_rot;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		
		if (collision({ d_step.x,0 })) {
			position.x += d_step.x;
		}
		
		if (collision({ 0,d_step.y })) {
			position.y += d_step.y;
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		if (collision({ -d_step.x,0 })) {
			position.x -= d_step.x;
		}

		if (collision({ 0, -d_step.y })) {
			position.y -= d_step.y;
		}

	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_window.close();

	m_player->getAngle() = angle;
	m_player->getPos() = position;


}


bool Engine::collision(sf::Vector2f delta) {

	auto world = MAPS[map_name].m_world;

	sf::Vector2f pos = m_player->getPos();
	
	if (world[(int)(pos.x + delta.x)][(int)(pos.y + delta.y)] > 0) {

		return false;

	}
	else {
		return true;
	}
}



sf::Color Engine::shading(float dist) {

	sf::Color shade = sf::Color::White;

	if (dist > 20) {
		shade.r /= 8;
		shade.g /= 8;
		shade.b /= 8;
	}
	if (dist < 20 && dist > 15) {
		shade.r /= 5;
		shade.g /= 5;
		shade.b /= 5;
	}
	if (dist < 15 && dist > 10) {
		shade.r /= 3;
		shade.g /= 3;
		shade.b /= 3;
	}
	if (dist < 10 && dist > 5) {
		shade.r /= 2;
		shade.g /= 2;
		shade.b /= 2;
	}

	return shade;

}