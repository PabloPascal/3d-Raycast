
#ifndef DEMON_H
#define DEMON_H


#include "Thing.h"
#include <Enemy.h>
#include "map.h"
#include <map>
#include <SFML/Graphics.hpp>
#include "animationSystem.hpp"





class Demon : public Enemy
{
	float 	m_speed;
	float   m_height;

	float 	enemy_size;
	float 	couldown_attack;
	float 	roar_time;

	int 	d_health;

	sf::Vector2f m_position;
	textureID m_textureID;
	

	bool m_AIactivate  	= false;
	bool m_IsCollision 	= false;
	bool m_IsAnimate 	= false; 
	bool m_isAlive;
	bool m_death_now	= true;
	bool m_running;
	bool m_attacking;
	bool finalyDead		= false;
	bool dying 			= false;
	bool get_damage 	= false;

	std::unique_ptr<Animation> run_animate = nullptr;
	std::unique_ptr<Animation> attack_animate = nullptr;
	std::unique_ptr<Animation> death_animate = nullptr;

	sf::Clock timer;
	sf::Clock roar_timer;
	sf::Clock damage_couldown_sound_time;

public:

	Demon() = default;
	Demon(sf::Vector2f position, textureID texture_id, 
        float speed, bool isCollision = false, 
		bool isAnimate = false, bool AIactivate = false);

	void update(Player& Player, const Map& map, float dt) override;

    void attack(Player&) override;

	void setPosition(const sf::Vector2f& pos) override;
	void setTexture(textureID texture_id) override;
	void setAIactivate(bool turn) override;

	textureID getTextureID() const override;
	float getSpeed() override;
	sf::Vector2f getPosition() const override;

	bool isAnimate() override;
	void setAnimate(bool isAnimate) override;
	void animation() override;
	void set_animations(TypeState type , textureID tex_id) override;

	bool getCollisionIndicate() override;
	void setCollision(bool collision) override;

	inline float getSize() override {return enemy_size;}
	inline void setHealth(int health) override {d_health = health;}
	inline int getHealth() override {return d_health;}
	inline bool isAlive() override {return !finalyDead;}
	inline void set_damage_indicate(bool is_dmg) override {get_damage = is_dmg;}
	inline bool is_get_damage() override {return get_damage;}
	inline float get_height() override {return m_height;};
};


#endif