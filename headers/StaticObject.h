#pragma once
#include "Thing.h"

class Object : public Thing
{
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Image m_image;

	bool m_IsCollision = false;
	bool m_IsAnimate = false;

public:
	Object() = default;
	Object(sf::Vector2f position, sf::Texture& texture, bool isCollision = false, bool isAnimate = false);

	sf::Vector2f getPosition() override;
	void setPosition(const sf::Vector2f& pos) override;
	sf::Texture& getTexture() override;
	sf::Image& getImage() override;
	void setTexture(sf::Texture& texture);
	void setImage(sf::Image& image);

	bool isAnimate() override;
	void setAnimate(bool isAnimate);

	bool getCollisionIndicate() override;
	void setCollision(bool collision);

};