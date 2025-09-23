#include "Demon.h"
#include "AI.h"
#include "Physics.h"
#include <random>
#include <cmath>



Demon::Demon(sf::Vector2f start_position, textureID texture_id, float speed, bool isCollision,
	bool isAnimate, bool AIactivate) : 
	m_IsCollision(isCollision), 
	m_IsAnimate(isAnimate), 
	m_AIactivate(AIactivate), 
	m_isAlive(true),
	m_running(true),
	m_attacking(false)
{
	std::srand(time(0));
	d_health = 20 + std::rand() % 5;


	m_position = start_position;
	m_textureID = texture_id;
	m_speed = speed;
	enemy_size = 0.6;
	couldown_attack = 900;

	run_animate = std::make_unique<Animation>(m_textureID, 200/m_speed, true);
	death_animate = std::make_unique<Animation>(500);
	attack_animate = std::make_unique<Animation>(300, true);
}



void Demon::update(Player& player, const Map& map, float dt) {
	
	if(d_health <= 0 && m_death_now){
		m_isAlive = false;
	}


	if(m_isAlive){
		if (m_AIactivate) {

			AI::simpleEnemyAI(this, player, map, dt);


		}
		if(m_IsAnimate){
			if(m_running){
				run_animate->update();
				m_textureID = run_animate->getCurrentAnimation();
			}
			
		}

		if(m_attacking){
			attack_animate->update([this]{m_attacking = false; m_running = true;});
			m_textureID = attack_animate->getCurrentAnimation();
		}

	}
	else{

		if(m_death_now){
			death_animate->update([this]{m_death_now = false;});
			m_textureID = death_animate->getCurrentAnimation();
			
		}else{
			finalyDead = true;
		}

	}

}


void Demon::animation(){}


void Demon::set_animations(TypeState type, textureID tex_id){
	switch (type)
	{
	case TypeState::run :
		run_animate->set_animation(tex_id);
		break;
	case TypeState::attack :
		attack_animate->set_animation(tex_id);
		break;
	case TypeState::death :
		death_animate->set_animation(tex_id);
		break;
	default:
		break;
	}

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



void Demon::attack(Player& player){

	if(timer.getElapsedTime().asMilliseconds() >= couldown_attack){
		
		m_attacking = true;
		m_running = false;

		player.setHealth(player.getHealth() - 5);
		

		std::cout << "Health: " << player.getHealth() << std::endl;
		timer.restart();
	}

}


