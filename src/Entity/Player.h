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



class Player {

	
	float m_playerSize;
	float m_jumpHeight;
	float m_speed;
	int m_health;

	bool isMove = false;
	bool isJumping;
	bool isFalling;
	bool isAlive;

	float TimeMove;

	float gravity = 10000;

	Camera* m_camera;

public:

	Player(float speed, Camera* camera);

	Camera* getCamera();

	const Camera* getCamera() const;

	void update(const Map& map, const std::vector<ThingPtr>& things, sf::RenderWindow& target, float dt);

	void jump(float dt);

	void hand(Weapon* weapon,float dt);

	inline void setHealth(int health) {m_health = health;}
	inline int getHealth() 	{return m_health;}

	void MouseInput(sf::RenderWindow& ,float dt);

	sf::Vector2f& getPos();
	float getPlayerSize();
	const float getJumpHeight();
	bool getIsJumping();
	bool getIsFalling();

};


#endif // !PLAYER_H
