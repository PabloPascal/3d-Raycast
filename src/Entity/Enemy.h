#pragma once
#include "Thing.h"


class Enemy :public Thing 
{
	float m_speed = 0.5;
	sf::Vector2f m_position;
	textureID m_textureID;


	bool m_AIactivate = false;
	bool m_IsCollision = false;
	bool m_IsAnimate = false;
public:
	Enemy() = default;
	Enemy(sf::Vector2f position, textureID texture_id, float speed, bool isCollision = false, 
		bool isAnimate = false, bool AIactivate = false);

	virtual void update(const sf::Vector2f& PlayerPos, float dt);


	virtual void setPosition(const sf::Vector2f& pos) override;
	virtual void setTexture(textureID texture_id);
	virtual void setAIactivate(bool turn);

	virtual textureID getTextureID() const override;
	virtual float getSpeed();
	virtual sf::Vector2f getPosition() const override;

	virtual bool isAnimate() override;
	virtual void setAnimate(bool isAnimate);

	virtual bool getCollisionIndicate() override;
	virtual void setCollision(bool collision);
};