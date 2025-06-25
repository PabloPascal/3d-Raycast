#include "../headers/Enemy.h"

Enemy::Enemy(sf::Vector2f position, sf::Texture& texture, float speed) {

	m_position = position;
	m_texture = texture;
	m_speed = speed;

}



void Enemy::update(float dt) {


}


sf::Vector2f Enemy::getPosition() {
	return m_position;
}

void Enemy::setPosition(const sf::Vector2f& pos) {
	m_position = pos;
}

sf::Image& Enemy::getImage() {
	return m_image;
}

sf::Texture& Enemy::getTexture() {
	return m_texture;
}


void Enemy::setTexture(sf::Texture& texture) {

	m_texture = texture;

}


void Enemy::setTexture(sf::Texture&& texture) {
	m_texture = std::move(texture);
}


void Enemy::setTexture(const std::string& string) {
	m_texture.loadFromFile(string);
}


float Enemy::getSpeed(){
	return m_speed;
}


void Enemy::setTexture(sf::Image&& image) {
	m_image = std::move(image);
}