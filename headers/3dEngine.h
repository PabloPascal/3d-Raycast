#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>
#include <vector>
#include <memory>

#include "../headers/map.h"
#include "../headers/Player.h";
#include "Render.h"
#include "ResourceHolder.h"




enum class textureID{
	wallbrick,
	floor,
	spriteTexture
};


class Engine {

	ResourceHolder<textureID, sf::Texture> mTextures;
	ResourceHolder<textureID, sf::Image> mImages;
	std::vector<Map> mMaps;
	std::vector<sf::Sprite> sprites;


	std::unique_ptr<Player> m_player;

	Renderer renderer;
	sf::RenderWindow m_window;

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
	
};


#endif // !ENGINE_H
