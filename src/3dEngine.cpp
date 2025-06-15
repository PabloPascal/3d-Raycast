#include "../headers/3dEngine.h"

#include <omp.h>
#include <iostream>
#include <string>

#define FLOOR_TEX 1



Engine::Engine(int ScreenWidth, int ScreenHeight, float fov, sf::Vector2f start_pos, float start_angle) {

	m_screen_width = ScreenWidth;
	m_screen_height = ScreenHeight;

	m_window.create(sf::VideoMode(m_screen_width, m_screen_height), "3d");

	m_player = std::make_unique<Player>(fov, start_angle, start_pos);


	float aspect = m_screen_width / (float)m_screen_height;
	plane = 0.5f * aspect * plane;

	resources = resources->getResourseHolder();

	
	wall.setPrimitiveType(sf::Lines);
	roof.setPrimitiveType(sf::Lines);
	floor.setPrimitiveType(sf::Lines);
	buffer.setPrimitiveType(sf::Points);

}


void Engine::changeMapName(std::string name) {
	map_name = name;
}



Engine::Ray Engine::RayCast(int x) {

	float angle = m_player->getAngle();
	float Fov = m_player->getFov();
	sf::Vector2f pos = m_player->getPos();
	//get world parameters
	auto world = resources->getMap(map_name).m_world;

	float Ray_angle = (angle - Fov / 2) + (float)x / (float)m_screen_width * Fov;

	sf::Vector2f ray_dir = { cos(Ray_angle), sin(Ray_angle) };

	sf::Vector2f dir = {cos(angle), sin(angle)};

	bool bHit = false;
	float dist = 0.f;
	float delta = 0.01;

	//distance from edge of grid
	float dx_side;
	float dy_side;
	sf::Vector2f camera_pos = pos - dir;

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

		if (test.x < 0 || test.x > world_width || test.y < 0 || test.y > world_height) {
			bHit = true;
			dist = m_depth;
		}


	}

	if (!isVertical) {
		dx_side = (pos.x + dist * ray_dir.x) - test.x;
		return { cos(Ray_angle - angle) * dist, dx_side};
	}
	else {
		dy_side = (pos.y + dist * ray_dir.y) - test.y;
		return { cos(Ray_angle - angle) * dist, dy_side};
	}

}




Engine::Ray Engine::FastRayCast(int x) {

	float cameraX = 2 * (float)x /(float)(m_screen_width) - 1; //-1 <= cameraX <= 1
	float perpendicualar_dist = 0;

	bool isHorizontal = false;

	sf::Vector2f pos = m_player->getPos();
	sf::Vector2f rayDir = dir - plane * cameraX;
	sf::Vector2f sideDist;
	sf::Vector2f deltaDist = { sqrt(1.0f + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
				sqrt(1.0f + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y)) };
	sf::Vector2i mapPos(pos);
	sf::Vector2f step;
	
	auto world = resources->getMap(map_name).m_world;


	if (rayDir.x < 0.0f) {
		step.x = -1;
		sideDist.x = (pos.x - mapPos.x) * deltaDist.x;
	}
	else {
		step.x = 1;
		sideDist.x = (mapPos.x + 1.0f - pos.x) * deltaDist.x;
	}
	if (rayDir.y < 0.0f) {
		step.y = -1;
		sideDist.y = (pos.y - mapPos.y) * deltaDist.y;
	}
	else {
		step.y = 1;
		sideDist.y = (mapPos.y + 1.0f - pos.y) * deltaDist.y;
	}

	while (world[mapPos.y][mapPos.x] == 0) {

		if (sideDist.x < sideDist.y) {
			sideDist.x += deltaDist.x;
			mapPos.x += step.x;
			isHorizontal = true;
			perpendicualar_dist = (mapPos.x - pos.x + (1 - step.x) / 2) / rayDir.x;
		}
		else {
			sideDist.y += deltaDist.y;
			mapPos.y += step.y;
			isHorizontal = false;
			perpendicualar_dist = (mapPos.y - pos.y + (1 - step.y) / 2) / rayDir.y;
		}


	}

	float wall_x;
	if (isHorizontal) {
		wall_x = pos.y + perpendicualar_dist * rayDir.y;
	}
	else {
		wall_x = pos.x + perpendicualar_dist * rayDir.x;
	}
	wall_x -= std::floor(wall_x);


	if (isHorizontal)
		return { perpendicualar_dist, wall_x };
	else
		return {perpendicualar_dist, wall_x};

}



void Engine::render(){

	Ray ray;
	int texture_block = resources->getTexture(wall_name).getSize().x;

	float textureFloor_w = resources->getTexture(floor_name).getSize().x;
	float textureFloor_h = resources->getTexture(floor_name).getSize().y;


	sf::Color shade;

	float wallHeight;
	float y_start_wall;
	float y_end_wall;
	
	int baseIndex = 0;

	wall.resize(2 * m_screen_width);
	roof.resize(2 * m_screen_width);
#if FLOOR_TEX == 0
	floor.resize(2 * m_screen_width);
#else
	buffer.resize(m_screen_width * m_screen_height / 2);
#endif

/*float angle = m_player->getAngle();
dir = { cos(angle),sin(angle)};
plane = { sin(angle), -cos(angle)};*/


#if FLOOR_TEX  
//#pragma omp parallel for

for (int y = m_screen_height / 2 + 1; y < m_screen_height; y++) {

	sf::Vector2f rayDirLeft = dir - plane;
	sf::Vector2f rayDirRight = dir + plane;
	

	int p = y - m_screen_height / 2.f;
	float posZ = 0.5 * m_screen_height;

	float rowDistance = posZ / (float)p;
	sf::Vector2f floorStep = rowDistance * (rayDirLeft - rayDirRight) / (float)m_screen_width;
		
	sf::Vector2f floorPos = m_player->getPos() + rowDistance*rayDirRight;



	for (int x = 0; x < m_screen_width; x++) {

		sf::Vector2i cell(floorPos);

		sf::Vector2i texCoords = {
			(int)(textureFloor_w * (floorPos.x - cell.x)) & (int)(textureFloor_w - 1),
			(int)(textureFloor_h * (floorPos.y - cell.y)) & (int)(textureFloor_h - 1)
		};

		floorPos += floorStep;

		int index = (y - m_screen_height / 2.f) * m_screen_width + x;
		buffer[index] = sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(texCoords));

	}

}


#endif
//#pragma omp parallel for
for (int x = 0; x < m_screen_width; x++) {

	Ray ray = FastRayCast(x);
	float distToWall = ray.dist;
	float delta_side = ray.delta_side;

	//texturing_buffer(x, distToWall, delta_side, texture_block);
	texturing(x, distToWall, delta_side, texture_block);

}

}



void Engine::add_map(std::string path, std::string map_Name) {

	map_name = map_Name;
	resources->loadMap(path, map_Name);
	world_width = resources->getMap(map_Name).size_x;
	world_height = resources->getMap(map_Name).size_y;
}

void Engine::add_map(map newMap, std::string map_Name) {

	map_name = map_Name;
	resources->loadMap(newMap, map_Name);
	world_width = resources->getMap(map_Name).size_x;
	world_height = resources->getMap(map_Name).size_y;
}



void Engine::run() {

	sf::Time timeSinceLastUpdate;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;


	while (m_window.isOpen()) {

		timeSinceLastUpdate = clock.restart();

		m_window.setTitle(std::to_string(1 / timeSinceLastUpdate.asSeconds()) + " FPS");

		sf::Event event;
		while (m_window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) m_window.close();
			if (event.type == sf::Event::KeyPressed){
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					m_window.close();
			}
			
			

		}

		render();
		//contol(timeSinceLastUpdate.asSeconds());
		transformation_coords(timeSinceLastUpdate.asSeconds());

		m_window.clear();
#if FLOOR_TEX
		m_window.draw(buffer, &resources->getTexture(floor_name));
#else
		m_window.draw(floor);
#endif

		m_window.draw(wall, &resources->getTexture(wall_name));
		m_window.draw(roof);

		m_window.display();


#if FLOOR_TEX
		buffer.clear();
#else		
	floor.clear();
#endif
	wall.clear();
	roof.clear();
	}
	
}

#include <iostream>

void Engine::contol(float dt) {

	float angle = m_player->getAngle();
	sf::Vector2f position = m_player->getPos();

	float speed_rot = 3;
	float speed = 5;

	sf::Vector2f d_step = { speed * dt * cos(angle), speed * dt * sin(angle) };
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		angle -= speed_rot * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle += speed_rot * dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

		if (collision({ position.x + speed * dir.x * dt , position.y })) {
			position.x += speed * dir.x * dt;
		}

		if (collision({ position.x, position.y + speed * dir.y * dt })) {
			position.y += speed * dir.y * dt;
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		if (collision({ position.x - speed * dir.x * dt , position.y })) {
			position.x -= speed * dir.x * dt;
		}

		if (collision({ position.x ,position.y - speed * dir.y * dt })) {
			position.y -= speed * dir.y * dt;
		}

	}

	m_player->getAngle() = angle;
	m_player->getPos() = position;


}


bool Engine::collision(sf::Vector2f pos) {

	auto world = resources->getMap(map_name).m_world;

	if (world[(int)(pos.y)][(int)(pos.x)] > 0) {

		return false;

	}
	else {
		return true;
	}
}



sf::Color Engine::shading(float dist) {

	sf::Color shade = sf::Color::White;
	if (dist >= m_depth - 1) {
		shade.a = 0.01;
		shade = sf::Color::Black;
	}

	if (dist > m_depth/1.5) {
		shade.r /= 8;
		shade.g /= 8;
		shade.b /= 8;
	}
	if (dist < m_depth/1.5 && dist > m_depth/2.f) {
		shade.r /= 5;
		shade.g /= 5;
		shade.b /= 5;
	}
	if (dist < m_depth/2.f && dist > m_depth/2.5) {
		shade.r /= 3;
		shade.g /= 3;
		shade.b /= 3;
	}
	if (dist < m_depth/2.5 && dist > m_depth/3) {
		shade.r /= 2;
		shade.g /= 2;
		shade.b /= 2;
	}

	return shade;

}



void Engine::texturing(int x, float distToWall, float delta_side, int texture_block) {
	
	sf::Color shade = shading(distToWall);

	int baseIndex = 2 * x;

	float wallHeight = (float)m_screen_height / distToWall;
	float y_start_wall = (m_screen_height - wallHeight) / 2;
	float y_end_wall = (m_screen_height + wallHeight) / 2;
	float texture_pos = delta_side* texture_block;

	//sf::Vector2u tex_size = resources->getTexture("walls").getSize();

	//wall
	wall[baseIndex] = (sf::Vertex(sf::Vector2f(x, y_start_wall), shade, sf::Vector2f(texture_pos, 0)));
	wall[baseIndex + 1] = (sf::Vertex(sf::Vector2f(x, y_end_wall), shade, sf::Vector2f(texture_pos, 64)));
	//std::cout << distToWall << std::endl;

	//roof
	roof[baseIndex] = (sf::Vertex(sf::Vector2f(x, 0), sf::Color(187, 211, 255)));
	roof[baseIndex + 1] = (sf::Vertex(sf::Vector2f(x, y_start_wall), sf::Color(187, 211, 255)));
	//floor
#if FLOOR_TEX == 0 
	floor[baseIndex] = (sf::Vertex(sf::Vector2f(x, y_end_wall), sf::Color::Black));
	floor[baseIndex + 1] = (sf::Vertex(sf::Vector2f(x, m_screen_height), sf::Color::White));
#endif

}



void Engine::transformation_coords(float dt) {

	float angle = m_player->getAngle();
	sf::Vector2f position = m_player->getPos();

	float rot_speed = 3;
	float rot = rot_speed * dt;
	float speed = 5;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		float prev_dirX = dir.x;
		dir.x = prev_dirX * cos(rot) - dir.y * sin(rot);
		dir.y = prev_dirX * sin(rot) + dir.y * cos(rot);
		
		float prev_planeX = plane.x;
		plane.x = prev_planeX * cos(rot) - plane.y * sin(rot);
		plane.y = prev_planeX * sin(rot) + plane.y * cos(rot);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		float prev_dirX = dir.x;
		dir.x = prev_dirX * cos(-rot) - dir.y * sin(-rot);
		dir.y = prev_dirX * sin(-rot) + dir.y * cos(-rot);

		float prev_planeX = plane.x;
		plane.x = prev_planeX * cos(-rot) - plane.y * sin(-rot);
		plane.y = prev_planeX * sin(-rot) + plane.y * cos(-rot);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

		if (collision({position.x + speed * dir.x * dt , position.y})) {
			position.x += speed * dir.x * dt;
		}

		if (collision({position.x, position.y + speed * dir.y * dt})) {
			position.y += speed * dir.y * dt;
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		if (collision({ position.x - speed * dir.x * dt , position.y })) {
			position.x -= speed * dir.x * dt;
		}

		if (collision({position.x ,position.y - speed * dir.y * dt })) {
			position.y -= speed * dir.y * dt;
		}

	}

	m_player->getPos() = position;

}


void Engine::EventProcess() {

	sf::Event event;
	while (m_window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) m_window.close();

		if (sf::Event::KeyPressed) {

		}

	}

}



void Engine::loadWallTexture(std::string path, std::string wallName)
{
	resources->loadTexture(path, wallName);
	wall_name = wallName;
}

void Engine::loadFloorTexture(std::string path, std::string floorName)
{
	resources->loadTexture(path, floorName);
	floor_name = floorName;
}



void Engine::loadImage(std::string path){


}


void handlePlayerInput(sf::Event event, bool isPressed) {}




void Engine::texturing_buffer(int x, float distToWall, float delta_side, int texture_block) {}