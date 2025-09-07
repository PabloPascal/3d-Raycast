#ifndef PLAYER_H
#define PLAYER_H
#include "Physics.h"
#include "Weapon.h"
#include "defines.h"
//#include "keyboardInput.h"

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


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

	
	float m_playerSize;
	float m_jumpHeight;
	float m_speed;

	bool isMove = false;
	bool isJumping;
	bool isFalling;

	float TimeMove;

	float gravity = 10000;

	Camera camera;

public:

	Player(float speed, sf::Vector2f start_pos);

	Camera& getCamera();

	const Camera getCamera() const;

	void update(const Map& map, const std::vector<ThingPtr>& things, sf::RenderWindow& target, float dt);

	void jump(float dt);

	void hand(Weapon* weapon, sf::RenderTarget& render_target, sf::Sprite& sprite,float dt);


	void MouseInput(sf::RenderWindow& ,float dt);

	sf::Vector2f& getPos();

	float getPlayerSize();

	const float getJumpHeight();

	bool getIsJumping();
	bool getIsFalling();

};


#endif // !PLAYER_H
