#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>


class Player {

	float m_fov;
	float m_angle = 0;
	sf::Vector2f m_position;
	float vertical_angle;
	float posZ;
	float playerSize;
	float jumpHeight;

	bool isJumping;
	bool isFalling;
public:

	Player(float fov, float start_angle, sf::Vector2f start_pos);

	float& getAngle();

	float& getVerticalAngle();

	float getFov();

	float& getZpos();

	sf::Vector2f& getPos();

	float getPlayerSize();

	const float getJumpHeight();

	bool& getIsJumping();
	bool& getIsFalling();

};


#endif // !PLAYER_H
