#include "../headers/Player.h"



Player::Player(float fov, float start_angle, sf::Vector2f start_pos) {

	m_fov = fov;
	m_angle = start_angle;
	m_position = start_pos;
	vertical_angle = 0;
	posZ = 0;
	playerSize = 0.15;

	isJumping = false;
	isFalling = false;
}

float& Player::getAngle() {
	return m_angle;
}

float Player::getFov() {
	return m_fov;
}

sf::Vector2f& Player::getPos() {
	return m_position;
}


float& Player::getVerticalAngle() {
	return vertical_angle;
}


float& Player::getZpos() {
	return posZ;
}


float Player::getPlayerSize() {
	return playerSize;
}



const float Player::getJumpHeight() {
	return jumpHeight;
}


bool& Player::getIsJumping() {
	return isJumping;
}

bool& Player::getIsFalling() {
	return isFalling;
}