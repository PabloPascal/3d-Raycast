#pragma once
#include "Thing.h"

class Object : public Thing
{
	sf::Vector2f m_position;
	textureID m_textureID;

	bool m_IsCollision = false;
	bool m_IsAnimate = false;

public:
	Object() = default;
	Object(sf::Vector2f position, textureID texture_id, bool isCollision = false, bool isAnimate = false);

	sf::Vector2f getPosition() override;
	void setPosition(const sf::Vector2f& pos) override;
	textureID getTextureID() override;
	void setTexture(textureID texture_id);

	bool isAnimate() override;
	void setAnimate(bool isAnimate);

	bool getCollisionIndicate() override;
	void setCollision(bool collision);

};