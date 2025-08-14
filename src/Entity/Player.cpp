#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>
#include <cmath>

Player::Player(float speed, sf::Vector2f start_pos) {

	camera.m_position = start_pos;
	camera.pitch = 0;
	camera.posZ = 0;
	m_speed = speed;

	m_playerSize = 0.15;

	isJumping = false;
	isFalling = false;

	TimeMove = 0;

}


Camera& Player::getCamera() {
	return camera;
}

const Camera Player::getCamera() const {
	return camera;
}


void Player::MouseInput(sf::RenderWindow& window,float dt) {

	float deltaX = (float)window.getSize().x/2 - sf::Mouse::getPosition(window).x;
	float deltaY = (float)window.getSize().y/2 - sf::Mouse::getPosition(window).y;
	


	float rot_speed = 3;
	float vertical_speed = 30;
	float rot = rot_speed * dt * abs(deltaX) / 50;
	float vertical_rot = vertical_speed * dt * abs(deltaY);
	float speed = 5;
	
	if (deltaX > 0) {
		float prev_dirX = camera.dir.x;
		camera.dir.x = prev_dirX * std::cos(rot) - camera.dir.y * std::sin(rot);
		camera.dir.y = prev_dirX * std::sin(rot) + camera.dir.y * std::cos(rot);

		float prev_planeX = camera.plane.x;
		camera.plane.x = prev_planeX * std::cos(rot) - camera.plane.y * std::sin(rot);
		camera.plane.y = prev_planeX * std::sin(rot) + camera.plane.y * std::cos(rot);
	}

	if (deltaX < 0) {
		float prev_dirX = camera.dir.x;
		camera.dir.x = prev_dirX * std::cos(-rot) - camera.dir.y * std::sin(-rot);
		camera.dir.y = prev_dirX * std::sin(-rot) + camera.dir.y * std::cos(-rot);

		float prev_planeX = camera.plane.x;
		camera.plane.x = prev_planeX * std::cos(-rot) - camera.plane.y * std::sin(-rot);
		camera.plane.y = prev_planeX * std::sin(-rot) + camera.plane.y * std::cos(-rot);
	}
	
	if (deltaY > 0) {
		camera.pitch += vertical_rot;
	}
	if (deltaY < 0) {
		camera.pitch -= vertical_rot;
	}


	sf::Mouse::setPosition(sf::Vector2i(window.getSize()) / 2, window);


}


void Player::update(const Map& map, const std::vector<ThingPtr>& things,sf::RenderWindow& window ,float dt) {


	float left_right_speed = 4;

	isMove = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

		isMove = true;
		TimeMove+=0.05;

		PhysicsEngine::PlayerCollisionReact(camera.dir, camera.m_position, map, m_speed, m_playerSize, things, window, dt);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

		isMove = true;
		TimeMove += 0.05;

		PhysicsEngine::PlayerCollisionReact(camera.dir, camera.m_position, map, -m_speed, -m_playerSize, things, window, dt);

	}

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

		isMove = true;
		TimeMove += 0.05;

		PhysicsEngine::PlayerCollisionReact(-camera.plane, camera.m_position, map, -left_right_speed, -m_playerSize, things, window, dt);


	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		isMove = true;
		TimeMove += 0.05;

		PhysicsEngine::PlayerCollisionReact(-camera.plane, camera.m_position, map, left_right_speed, m_playerSize, things, window, dt);


	}


	MouseInput(window,dt);


	jump(dt);


}


sf::Vector2f& Player::getPos() {
	return camera.m_position;
}



float Player::getPlayerSize() {
	return m_playerSize;
}



const float Player::getJumpHeight() {
	return m_jumpHeight;
}


bool Player::getIsJumping() {
	return isJumping;
}

bool Player::getIsFalling() {
	return isFalling;
}



void Player::hand(Weapon* weapon, sf::RenderTarget& render_target, sf::Sprite& hand_sprite, float dt) {

	if (TimeMove > 1000) {
		TimeMove = (int)TimeMove % 1000;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		weapon->shoot();
	}

	float amplitude = 0.5;

	if(isMove)
		hand_sprite.setPosition(hand_sprite.getPosition().x, 
		hand_sprite.getPosition().y - amplitude * sin(TimeMove));
	
	

	render_target.draw(hand_sprite);

}



void Player::jump(float dt) {

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