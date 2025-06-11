#include "../headers/Player.h"



Player::Player(float fov, float start_angle, sf::Vector2f start_pos) {

	m_fov = fov;
	m_angle = start_angle;
	m_position = start_pos;

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
