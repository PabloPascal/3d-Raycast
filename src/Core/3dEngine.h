#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>
#include <vector>
#include <memory>

#include "map.h"
#include "Renderer.h"
#include "AI.h" 




class Engine : public Renderer
{

	std::unique_ptr<Player> m_player;


public:
	Engine(size_t screen_width, size_t screen_hight);

	void run();

	
	void loadMap(const std::string& path);
	void loadMap(Map& map);
	void loadTexture(textureID id,const std::string& path);
	void loadTexture();
	void loadImage(const std::string& path);
	void loadImage();
	void loadSprite();
	void loadThing();
	void loadEnemy(sf::Vector2f startPos, float speed, textureID tid,bool isCollsion, bool isAnimate, bool AI);
	void loadStaticObject(sf::Vector2f startPos, textureID tid, bool isCollsion, bool isAnimate);

};


#endif // !ENGINE_H
