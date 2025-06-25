#pragma once
#include "Thing.h"



class Enemy :public Thing 
{
	float m_speed = 0.5;
	sf::Vector2f m_position;
	sf::Image m_image;
	sf::Texture m_texture;
	

public:
	Enemy() = default;
	Enemy(sf::Vector2f position, sf::Texture& texture, float speed);

	void update(float dt);


	void setPosition(const sf::Vector2f& pos) override;
	void setTexture(sf::Texture& texture);
	void setTexture(sf::Texture&& texture);
	void setTexture(const std::string& string);
	void setTexture(sf::Image&& image);

	sf::Image& getImage() override;
	sf::Texture& getTexture() override;
	float getSpeed();
	sf::Vector2f getPosition() override;

};