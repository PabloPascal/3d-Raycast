#pragma once
#include "Thing.h"



class Enemy :public Thing 
{
	float m_speed = 0.5;
	sf::Vector2f m_position;
	textureID m_textureID;

	bool m_IsCollision = false;
	bool m_IsAnimate = false;
public:
	Enemy() = default;
	Enemy(sf::Vector2f position, textureID texture_id, float speed, bool isCollision = false, 
		bool isAnimate = false);

	void update(float dt);


	void setPosition(const sf::Vector2f& pos) override;
	void setTexture(textureID texture_id);

	textureID getTextureID() override;
	float getSpeed();
	sf::Vector2f getPosition() override;

	bool isAnimate() override;
	void setAnimate(bool isAnimate);

	bool getCollisionIndicate() override;
	void setCollision(bool collision);
};