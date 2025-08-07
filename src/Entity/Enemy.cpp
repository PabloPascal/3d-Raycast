#include "Enemy.h"
#include "AI.h"
#include "Physics.h"
#include <cmath>

Enemy::Enemy(sf::Vector2f position, textureID texture_id, float speed, bool isCollision,
	bool isAnimate, bool AIactivate) : m_IsCollision(isCollision), m_IsAnimate(isAnimate), m_AIactivate(AIactivate)
{

	m_position = position;
	m_textureID = texture_id;
	m_speed = speed;
	enemy_size = 0.6;

}



void Enemy::update(const sf::Vector2f& playerPos, const Map& map, float dt) {

	if (m_AIactivate) {


		sf::Vector2f dir = AI::simpleAI(m_position, playerPos, dt);

		sf::Vector2f move = dir * m_speed * dt;
		sf::Vector2f newPos = m_position + move;

		float xOffset = move.x > 0 ? enemy_size / 2 : -enemy_size / 2;
		float yOffset = move.y > 0 ? enemy_size / 2 : -enemy_size / 2;

		//std::cout << "m_pos = {" << m_position.x << ", " << m_position.y << "}" << std::endl;
		if (m_IsCollision) {

			if (PhysicsEngine::checkEnemyMapCollision(map, {newPos.x + xOffset, m_position.y}, enemy_size, false)) 
			{
				m_position.x = newPos.x;
			}
			if(PhysicsEngine::checkEnemyMapCollision(map, {m_position.x, newPos.y + yOffset}, enemy_size, true)) {
				m_position.y = newPos.y;
			}

		}else{
			m_position = newPos;
		}


	}



}


sf::Vector2f Enemy::getPosition() const {
	return m_position;
}

void Enemy::setPosition(const sf::Vector2f& pos) {
	m_position = pos;
}


textureID Enemy::getTextureID() const {
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



void Enemy::setAIactivate(bool turn) {
	m_AIactivate = turn;
}