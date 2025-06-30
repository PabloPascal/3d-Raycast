#include "../headers/Enemy.h"

Enemy::Enemy(sf::Vector2f position, textureID texture_id, float speed, bool isCollision,
	bool isAnimate) : m_IsCollision(isCollision), m_IsAnimate(isAnimate)
{

	m_position = position;
	m_textureID = texture_id;
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


textureID Enemy::getTextureID() {
	return m_textureID;
}


void Enemy::setTexture(textureID texture_id) {
	m_textureID = texture_id;

}



float Enemy::getSpeed(){
	return m_speed;
}


bool Enemy::getCollisionIndicate() {
	return m_IsCollision;
}


void Enemy::setCollision(bool collision) {
	m_IsCollision = collision;
}


bool Enemy::isAnimate() {
	return m_IsAnimate;
}

void Enemy::setAnimate(bool isAnimate){
	m_IsAnimate = isAnimate;
}