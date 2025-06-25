#pragma once
#include "Thing.h"

class Object : public Thing
{
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Image m_image;

public:
	Object() = default;
	Object(sf::Vector2f position, sf::Texture& texture);
	sf::Vector2f getPosition() override;
	void setPosition(const sf::Vector2f& pos) override;
	sf::Texture& getTexture() override;
	sf::Image& getImage() override;
	void setTexture(sf::Texture& texture);
	void setImage(sf::Image& image);

};