
#pragma once
#include "Thing.h"
#include <Enemy.h>
#include "map.h"
#include <map>
#include <SFML/Graphics.hpp>


class Demon : public RenderebleThing, public Enemy
{
	float m_speed = 0.5;
	sf::Vector2f m_position;
	textureID m_textureID;
	float enemy_size;

	bool m_AIactivate = false;
	bool m_IsCollision = false;
	bool m_IsAnimate = false;

	int m_current_animation_key;
	int m_animation_count;
	std::map<int, textureID> m_animation_state; 

	sf::Clock timer;
	float time;

public:
	Demon() = default;
	Demon(sf::Vector2f position, textureID texture_id, 
        float speed, bool isCollision = false, 
		bool isAnimate = false, bool AIactivate = false);

	void update(const Player& Player, const Map& map, float dt) override;

    void attack() override;

	void setPosition(const sf::Vector2f& pos) override;
	void setTexture(textureID texture_id) override;
	void setAIactivate(bool turn) override;

	textureID getTextureID() const override;
	float getSpeed() override;
	sf::Vector2f getPosition() const override;

	bool isAnimate() override;
	void setAnimate(bool isAnimate) override;

	void animation() override;
	void add_animations(textureID tex_id) override;

	bool getCollisionIndicate() override;
	void setCollision(bool collision) override;
};