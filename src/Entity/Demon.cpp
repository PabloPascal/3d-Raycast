#include "Demon.h"
#include "AI.h"
#include "Physics.h"
#include <cmath>

Demon::Demon(sf::Vector2f start_position, textureID texture_id, float speed, bool isCollision,
	bool isAnimate, bool AIactivate) : m_IsCollision(isCollision), m_IsAnimate(isAnimate), m_AIactivate(AIactivate)
{

	m_position = start_position;
	m_textureID = texture_id;
	m_speed = speed;
	enemy_size = 0.6;

	animate = std::make_unique<Animation>(m_textureID, 200/m_speed);
}



void Demon::update(const Player& player, const Map& map, float dt) {
	

	if (m_AIactivate) {

		AI::simpleEnemyAI(this, player, map, dt);


	}
	if(m_IsAnimate){

		animate->update();
		m_textureID = animate->getCurrentAnimation();
	}


}



void Demon::animation(){

}




void Demon::set_animations(textureID tex_id){

	animate->set_animation(tex_id);

}





sf::Vector2f Demon::getPosition() const {
	return m_position;
}

void Demon::setPosition(const sf::Vector2f& pos) {
	m_position = pos;
}


textureID Demon::getTextureID() const {
	return m_textureID;
}


void Demon::setTexture(textureID texture_id) {
	m_textureID = texture_id;

}



float Demon::getSpeed(){
	return m_speed;
}


bool Demon::getCollisionIndicate() {
	return m_IsCollision;
}


void Demon::setCollision(bool collision) {
	m_IsCollision = collision;
}


bool Demon::isAnimate() {
	return m_IsAnimate;
}

void Demon::setAnimate(bool isAnimate){
	m_IsAnimate = isAnimate;
}



void Demon::setAIactivate(bool turn) {
	m_AIactivate = turn;
}



void Demon::attack(){

    std::cout << "smth";

}



float Demon::getEnemySize() {

	return enemy_size;

}

