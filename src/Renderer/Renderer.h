
#ifndef RENDERER 
#define RENDERER 

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "MathLib.h"


#define NUM_THREADS 8


class Renderer
{

public:

	Renderer(sf::RenderWindow& window);

	Renderer(const Renderer&) = delete;

	Renderer& operator=(const Renderer&) = delete;

	void render(const Camera& camera, const wallSprite&);
	
private:

	void renderFloor(const Camera& camera, const size_t y_start,const size_t y_end);
	
	void renderRowFloor(const Camera& camera, const size_t y);

	void renderEntity(const Camera& camera);
	
	void renderPerSprite(const Camera& camera, ThingPtr& thing);

	void multithreadRenderFloor(const Camera& camera);

	void spriteSort();

	sf::Color shading(float dist);

	void renderWall(int x, float distToWall, float delta_side,
			 const Camera& camera, int wall_id, const wallSprite&);


private:

	sf::Color roofColor;

	std::vector<float> 	zBuffer;
	std::vector<int> 	spriteOrder;
	std::vector<float> 	spriteDist;


	sf::VertexArray m_roofVertexArray;
	sf::VertexArray m_wallVertexArray;
	sf::VertexArray m_floorVertexArray;
	sf::VertexArray m_spriteColumnsVertexArray;

	uint8_t* m_pfloorPixels;


	sf::VertexArray debugCollum;


	sf::RenderWindow* m_window = nullptr;

	size_t numThings;

	size_t m_ScreenWidth;
	size_t m_ScreenHeight;

	float m_depth;


};



#endif