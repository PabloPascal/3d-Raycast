#ifndef PLAYER_H
#define PLAYER_H
#include "Physics.h"

struct Camera {
	[[maybe_unused]] float m_angle = 0;//angle with OX
	[[maybe_unused]] float m_fov = 0; //unused

	sf::Vector2f dir = { 1, 0 };
	sf::Vector2f plane = { 0, 0.66 };

	sf::Vector2f m_position;
	float posZ = 0;
	float pitch;
};

class Player {

	
	float playerSize;
	float jumpHeight;

	bool isJumping;
	bool isFalling;

	float gravity = 10000;

	Camera camera;

public:

	Player(float fov, float start_angle, sf::Vector2f start_pos);

	Camera& getCamera();

	const Camera getCamera() const;

	void control(const Map& map, const std::vector<ThingPtr>& things, float dt);


	sf::Vector2f& getPos();

	float getPlayerSize();

	const float getJumpHeight();

	bool getIsJumping();
	bool getIsFalling();

};


#endif // !PLAYER_H
