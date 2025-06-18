#include "../headers/3dEngine.h"

#include <omp.h>
#include <iostream>
#include <string>

#if NDEBUG
#define FLOOR_TEX 1
#else 
#define FLOOR_TEX 0
#endif


Engine::Engine(int ScreenWidth, int ScreenHeight, float fov, sf::Vector2f start_pos, float start_angle) 
{

	m_screen_width = ScreenWidth;
	m_screen_height = ScreenHeight;

	cameraHeight = 0.5;

	m_window.create(sf::VideoMode(m_screen_width, m_screen_height), "3d");

	m_player = std::make_unique<Player>(fov, start_angle, start_pos);

	float aspect = m_screen_width / (float)m_screen_height;
	plane = 0.5f * aspect * plane;
	
	wall.setPrimitiveType(sf::Lines);
	roof.setPrimitiveType(sf::Lines);
	floor.setPrimitiveType(sf::Lines);
	buffer.setPrimitiveType(sf::Points);

}


void Engine::loadMap(std::string path) {

	mMaps.load(path);

}


void Engine::loadMap(map& Map) {
	mMaps = Map;
}


void Engine::loadTexture() {

	mTextures.load(textureID::wallbrick, std::string("../res/redbrick.png"));
	mTextures.load(textureID::floor, std::string("../res/colorstone.png"));
	
}

void Engine::loadTexture(std::string path) {

	mTextures.load(textureID::wallbrick, path);

}

void Engine::loadImage() {
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
		m_window.draw(buffer, &mTextures.get(textureID::floor));
#else
		m_window.draw(floor);
#endif

		m_window.draw(wall, &mTextures.get(textureID::wallbrick));
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

	auto world = mMaps.m_world;

	if (world[(int)(pos.y)][(int)(pos.x)] > 0) {

		return false;

	}
	else {
		return true;
	}
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

	float size = m_player->getPlayerSize();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (dir.x > 0 && collision({ position.x + speed * dir.x * dt + size, position.y})) {
			position.x += speed * dir.x * dt;
		}
		
		if (dir.x < 0 && collision({ position.x + speed * dir.x * dt - size, position.y })) {
			position.x += speed * dir.x * dt;
		}

		if (dir.y > 0 && collision({position.x, position.y + speed * dir.y * dt + size})) {
			position.y += speed * dir.y * dt;
		}

		if (dir.y < 0 && collision({ position.x, position.y + speed * dir.y * dt - size })) {
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

#if FLOOR_TEX == 0
	float vertical_speed = 500 * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_player->getVerticalAngle() = m_player->getVerticalAngle() - vertical_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_player->getVerticalAngle() = m_player->getVerticalAngle() + vertical_speed;
	}

	//jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_player->getIsFalling()) {
		cameraHeight += 0.1;
		m_player->getIsJumping() = true;

	}

	if (m_player->getIsJumping()) {

		cameraHeight += dt;
		if (cameraHeight >= 0.9) {
			m_player->getIsJumping() = false;
			m_player->getIsFalling() = true;
		}

	}

	if (m_player->getIsFalling()) {
		cameraHeight -= dt;
		if (cameraHeight < 0.5) {
			m_player->getIsFalling() = false;
		}
	}
#endif

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

