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
	sf::Sprite weaponSprite;
	sf::Sprite aim;

	Weapon* weapon;

public:
	Engine(const size_t screen_width, const size_t screen_height, const std::string& absolute_path);

	void run();

	
	void loadMap(mapID,const std::string& path);
	void loadTexture(textureID id, const std::string& path);
	void loadImage(textureID id, const std::string& path);

	void loadMap(mapID ,Map& map);

	void loadTexture();
	void loadImage();
	void loadSprite();
	void loadThing();

	void loadEnemy(sf::Vector2f startPos, float speed, textureID tid,bool isCollsion, bool isAnimate, bool AI);
	void loadStaticObject(sf::Vector2f startPos, textureID tid, bool isCollsion, bool isAnimate);

};


#endif // !ENGINE_H
