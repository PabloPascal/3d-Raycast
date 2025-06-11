#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>


class Player {

	float m_fov;
	float m_angle = 0;
	sf::Vector2f m_position;


public:

	Player(float fov, float start_angle, sf::Vector2f start_pos);

	float& getAngle();

	float getFov();

	sf::Vector2f& getPos();

};


#endif // !PLAYER_H
