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
	enemy_size = 0.1;

}



void Enemy::update(const sf::Vector2f& playerPos, const Map& map, float dt) {

	if (m_AIactivate) {


		sf::Vector2f dir = AI::simpleAI(m_position, playerPos, dt);


		sf::Vector2f newPos = m_position + dir * m_speed * dt;


		if (m_IsCollision) {
			sf::Vector2f delta;
			if (!PhysicsEngine::checkEnemyMapCollision(map, m_position + dir * m_speed * dt, delta, 0)) {
				
				sf::Vector2f CenterBlock = { std::floor(m_position.x + delta.x) + 0.5f, std::floor(m_position.y + delta.x) + 0.5f};
				sf::Vector2f normal = -PhysicsEngine::findNormal(m_position + delta, CenterBlock);

				std::cout << "normal: (" << normal.x << ", " << normal.y << ")\n";
				sf::Vector2f perp_normal = { abs(normal.y), abs(normal.x) };

				m_position += m_speed * normal * dt;

			}
			else {
				m_position = newPos;
			}

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