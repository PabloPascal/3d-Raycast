#ifndef RESOURCE_HOLDER
#define RESOURCE_HOLDER


#include <string>
#include <unordered_map>
#include <fstream>
#include <memory>
#include <cassert>
#include <SFML/Graphics/Texture.hpp>


#include "defines.h"
#include "map.h"
#include "soundSystem.hpp"




class ResourceManager
{

	std::unordered_map<textureID, std::unique_ptr<sf::Texture>>  	mTextures;
	std::unordered_map<textureID, std::unique_ptr<sf::Image>>  		mImages;
	std::unordered_map<mapID, std::unique_ptr<Map>>					mMaps;
	SoundManager 													sound_manager;


	static ResourceManager* _instance;

	ResourceManager(const ResourceManager& ) = delete;
	ResourceManager& operator = (const ResourceManager& ) = delete;
	ResourceManager() = default;

public:

	static ResourceManager* getInstance();


	void loadTexture(const textureID texture_id, const std::string& filePath);
	void loadImage(const textureID iamge_id, const std::string& filePath);
	void loadSound(const soundID sound_id, const std::string& filePath);
	void loadMap(const mapID map_id, const std::string& filePath);

	sf::Texture& getTexture(const textureID texture_id);
	sf::Image& getImage(const textureID image_id);
	
	const Map& getMap(const mapID map_id) const;
	const sf::Texture& getTexture(const textureID texture_id) const;
	const sf::Image& getImage(const textureID image_id) const;


	void play(const soundID sound_id);


	void removeTexture(const textureID texture_id);
	void removeImage(const textureID image_id);




};


#endif