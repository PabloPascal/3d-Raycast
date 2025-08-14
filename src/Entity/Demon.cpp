#include "Demon.h"
#include "AI.h"
#include "Physics.h"
#include <cmath>

Demon::Demon(sf::Vector2f start_position, textureID texture_id, float speed, bool isCollision,
	bool isAnimate, bool AIactivate) : m_IsCollision(isCollision), m_IsAnimate(isAnimate), m_AIactivate(AIactivate)
{

	m_current_animation_key = 0;
	m_animation_count = 0;


	m_position = start_position;
	m_textureID = texture_id;
	m_speed = speed;
	enemy_size = 0.6;


	time = 0;
}



void Demon::update(const Player& player, const Map& map, float dt) {
	
	time += timer.getElapsedTime().asSeconds();

	if (m_AIactivate) {

		AI::simpleEnemyAI(this, player, map, dt);


	}
	if(m_IsAnimate){

		animation();

	}


}



void Demon::animation(){

	if(time > 0.5){
		if(m_current_animation_key < m_animation_count){

			m_textureID = m_animation_state[m_current_animation_key];
			m_current_animation_key++;

			}
		else{
			m_current_animation_key = 0;
			m_textureID = m_animation_state[m_current_animation_key];
		}

		time = 0;
		timer.restart();

	}
	

}




void Demon::add_animations(textureID tex_id){

	//std::cout << "tex_id = " << (int)tex_id << ", m_animation_count: "<< m_animation_count << std::endl;

	m_animation_state.emplace(m_animation_count, tex_id);
	m_animation_count++;

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

