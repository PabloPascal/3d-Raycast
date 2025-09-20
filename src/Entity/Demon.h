
#ifndef DEMON_H
#define DEMON_H


#include "Thing.h"
#include <Enemy.h>
#include "map.h"
#include <map>
#include <SFML/Graphics.hpp>
#include "animationSystem.hpp"


class Demon : public RenderableThing, public Enemy
{
	float m_speed = 0.5;
	sf::Vector2f m_position;
	textureID m_textureID;
	float enemy_size;

	bool m_AIactivate = false;
	bool m_IsCollision = false;
	bool m_IsAnimate = false;

	std::unique_ptr<Animation> animate = nullptr;


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
	void set_animations(textureID tex_id) override;

	bool getCollisionIndicate() override;
	void setCollision(bool collision) override;

	float getEnemySize() override;
};


#endif