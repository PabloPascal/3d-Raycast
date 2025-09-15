#pragma once
#include "Thing.h"


class StaticObject : public RenderableThing
{
	sf::Vector2f m_position;
	textureID m_textureID;

	bool m_IsCollision = false;
	bool m_IsAnimate = false;

public:
	StaticObject() = default;
	StaticObject(sf::Vector2f position, textureID texture_id, bool isCollision = false, bool isAnimate = false);

	sf::Vector2f getPosition() const override;
	void setPosition(const sf::Vector2f& pos) override;
	textureID getTextureID() const override;
	void setTexture(textureID texture_id) override;

	bool isAnimate() override;
	void setAnimate(bool isAnimate);

	bool getCollisionIndicate() override;
	void setCollision(bool collision) override;

};