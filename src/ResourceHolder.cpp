#include "../headers/ResourceHolder.h"
#include <fstream>
#include <iostream>
#include <sstream>

ResourceHolder* ResourceHolder::resourseHolder = nullptr;

ResourceHolder* ResourceHolder::getResourseHolder() {

	if (resourseHolder != nullptr) {
		return resourseHolder;
	}

	resourseHolder = new ResourceHolder;
	return resourseHolder;
}


void ResourceHolder::loadMap(std::string path, std::string map_name) {

	if (Maps.find(map_name) != Maps.end()) {
		std::cout << "map is already exist";
		return;
	}

	map mapFile;
	mapFile.load(path);


	Maps.insert(std::make_pair(map_name, mapFile));

}


void ResourceHolder::loadMap(map newMap, std::string map_name) {
	
	Maps.insert(std::make_pair(map_name, newMap));
}



void ResourceHolder::loadTexture(std::string path, std::string texture_name) {
	sf::Texture texture;

	texture.loadFromFile(path);
	Textures.insert(std::make_pair(texture_name, texture));

}

void ResourceHolder::loadImage(std::string path, std::string image_name)
{
	sf::Image image;

	image.loadFromFile(path);
	Images.insert(std::make_pair(image_name, image));

}


map ResourceHolder::getMap(std::string map_name){
	return Maps[map_name];
}

sf::Texture ResourceHolder::getTexture(std::string texture_name){
	return Textures[texture_name];
}


sf::Image ResourceHolder::getImage(std::string image_name){
	return Images[image_name];
}