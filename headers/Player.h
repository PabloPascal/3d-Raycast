#ifndef PLAYER_H
#define PLAYER_H
#include "Physics.h"

struct Camera {
	float m_angle = 0;//angle with OX

	sf::Vector2f dir = { 1, 0 };
	sf::Vector2f plane = { 0, 0.66 };

	sf::Vector2f m_position;
	float posZ;

};

class Player {

	float m_fov;
	float vertical_angle;
	float playerSize;
	float jumpHeight;

	bool isJumping;
	bool isFalling;

	Camera camera;

public:

	Player(float fov, float start_angle, sf::Vector2f start_pos);

	Camera getCamera();

	const Camera getCamera() const;

	void control(const Map& map, const std::vector<ThingPtr>& things, float dt);


	float& getAngle();

	float& getVerticalAngle();

	float getFov();

	float& getZpos();

	sf::Vector2f& getPos();

	float getPlayerSize();

	const float getJumpHeight();

	bool getIsJumping();
	bool getIsFalling();

};


#endif // !PLAYER_H
