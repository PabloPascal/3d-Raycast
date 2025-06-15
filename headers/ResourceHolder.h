#pragma once
#include <string>
#include "map.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>

class ResourceHolder {

	std::unordered_map<std::string, map> Maps; //our game map
	std::unordered_map<std::string, sf::Texture> Textures;
	std::unordered_map<std::string, sf::Image> Images;


	static ResourceHolder* resourseHolder;

public:

	static ResourceHolder* getResourseHolder();

	//name is the key, (name of map)
	void loadMap(std::string path, std::string name);
	void loadMap(map, std::string name);
	
	void loadTexture(std::string path, std::string name);
	void loadImage(std::string path, std::string name);
	

	map getMap(std::string map_name);
	sf::Texture getTexture(std::string texture_name);
	sf::Image getImage(std::string image_name);
};