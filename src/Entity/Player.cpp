#include "Player.h"
#include <iostream>

Player::Player(float fov, float start_angle, sf::Vector2f start_pos) {

	camera.m_fov = fov;
	camera.m_angle = start_angle;
	camera.m_position = start_pos;
	camera.pitch = 0;
	camera.posZ = 0;
	
	playerSize = 0.15;

	isJumping = false;
	isFalling = false;
}


Camera& Player::getCamera() {
	return camera;
}

const Camera Player::getCamera() const {
	return camera;
}

void Player::control(const Map& map, const std::vector<ThingPtr>& things, float dt) {

	float rot_speed = 3;
	float rot = rot_speed * dt;
	float speed = 5;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		float prev_dirX = camera.dir.x;
		camera.dir.x = prev_dirX * cos(rot) - camera.dir.y * sin(rot);
		camera.dir.y = prev_dirX * sin(rot) + camera.dir.y * cos(rot);

		float prev_planeX = camera.plane.x;
		camera.plane.x = prev_planeX * cos(rot) - camera.plane.y * sin(rot);
		camera.plane.y = prev_planeX * sin(rot) + camera.plane.y * cos(rot);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		float prev_dirX = camera.dir.x;
		camera.dir.x = prev_dirX * cos(-rot) - camera.dir.y * sin(-rot);
		camera.dir.y = prev_dirX * sin(-rot) + camera.dir.y * cos(-rot);

		float prev_planeX = camera.plane.x;
		camera.plane.x = prev_planeX * cos(-rot) - camera.plane.y * sin(-rot);
		camera.plane.y = prev_planeX * sin(-rot) + camera.plane.y * cos(-rot);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (camera.dir.x > 0 && PhysicsEngine::checkCollision(map, { camera.m_position.x + speed * camera.dir.x * dt + playerSize, camera.m_position.y }, things)) {
			camera.m_position.x += speed * camera.dir.x * dt;
		}
		if (camera.dir.x < 0 && PhysicsEngine::checkCollision(map, { camera.m_position.x + speed * camera.dir.x * dt - playerSize, camera.m_position.y }, things)) {
			camera.m_position.x += speed * camera.dir.x * dt;
		}
		
		if (camera.dir.y > 0 && PhysicsEngine::checkCollision(map, { camera.m_position.x, camera.m_position.y + speed * camera.dir.y * dt + playerSize }, things)) {
			camera.m_position.y += speed * camera.dir.y * dt;
		}

		if (camera.dir.y < 0 && PhysicsEngine::checkCollision(map, { camera.m_position.x, camera.m_position.y + speed * camera.dir.y * dt - playerSize }, things)) {
			camera.m_position.y += speed * camera.dir.y * dt;
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		if (PhysicsEngine::checkCollision(map, { camera.m_position.x - speed * camera.dir.x * dt , camera.m_position.y }, things)) {
			camera.m_position.x -= speed * camera.dir.x * dt;
		}

		if (PhysicsEngine::checkCollision(map, { camera.m_position.x , camera.m_position.y - speed * camera.dir.y * dt }, things)) {
			camera.m_position.y -= speed * camera.dir.y * dt;
		}


	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		camera.pitch += 850*dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		camera.pitch -= 850 * dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping && !isFalling) {
		gravity = 1000;
		isJumping = true;
	}


#define MAX_HEIGHT 250
	
	if (isJumping) {
		gravity -= 10;
		camera.posZ += gravity * dt;
	}

	if (camera.posZ > MAX_HEIGHT || gravity < 10) {
		isFalling = true;
		isJumping = false;
		
	}
	/*std::cout <<"posZ = " << camera.posZ << std::endl;
	std::cout << "isFall = " << isFalling << std::endl;*/
	//std::cout << "gravity = " << gravity << std::endl;


	if (isFalling) {
		gravity += 20;
		camera.posZ -= gravity * dt;
	}

	if (camera.posZ <= 0) {
		isFalling = false;
	}

}


sf::Vector2f& Player::getPos() {
	return camera.m_position;
}



float Player::getPlayerSize() {
	return playerSize;
}



const float Player::getJumpHeight() {
	return jumpHeight;
}


bool Player::getIsJumping() {
	return isJumping;
}

bool Player::getIsFalling() {
	return isFalling;
}