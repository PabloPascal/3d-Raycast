
#include "ResourceHolder.h"

#include <iostream>

ResourceManager* ResourceManager::_instance = nullptr;



ResourceManager* ResourceManager::getInstance(){

	if(_instance == nullptr){
		_instance = new ResourceManager;
	}
	return _instance;
}



void ResourceManager::loadTexture(const textureID texture_id, const std::string& filePath)
	{

		if(mTextures.find(texture_id) == mTextures.end()){
			
			sf::Texture texture;
			texture.loadFromFile(filePath);
			
			mTextures.insert(std::make_pair( 
				texture_id, 
				std::make_unique<sf::Texture>(std::move(texture))  
			));


		}

	}
	

void ResourceManager::loadImage(const textureID image_id, const std::string& filePath)
	{


		if(mImages.find(image_id) == mImages.end()){

			sf::Image image;
			image.loadFromFile(filePath);

			mImages.insert(std::make_pair( 
				image_id, 
				std::make_unique<sf::Image>(std::move(image))  
			));


		}

	}


void ResourceManager::loadSound(const soundID sound_id, const std::string& filePath)
	{
		sound_manager.loadSound(sound_id, filePath);
	}


sf::Texture& ResourceManager::getTexture(const textureID texture_id)
	{
		if(mTextures.find(texture_id) == mTextures.end()){
			std::cout << "cannot find texture: id = " << static_cast<int>(texture_id) << std::endl;
		}
		return *mTextures[texture_id];
	}


sf::Image& ResourceManager::getImage(const textureID image_id)
	{
		if(mTextures.find(image_id) == mTextures.end()){
			std::cout << "cannot find image: id = " << static_cast<int>(image_id) << std::endl;
		}
		return *mImages[image_id];
	}

const sf::Texture& ResourceManager::getTexture(const textureID texture_id) const
	{
		if(mTextures.find(texture_id) == mTextures.end()){
			std::cout << "cannot find texture: id = " << static_cast<int>(texture_id) << std::endl;
		}
		return *mTextures.find(texture_id)->second;
	}


const sf::Image& ResourceManager::getImage(const textureID image_id) const
	{
		if(mTextures.find(image_id) == mTextures.end()){
			std::cout << "cannot find image: id = " << static_cast<int>(image_id) << std::endl;
		}
		return *mImages.find(image_id)->second;
	}



const Map& ResourceManager::getMap(const mapID map_id) const{

    if(mMaps.find(map_id) == mMaps.end() ){
        std::cout << "cannot find map: id = " << static_cast<int>(map_id) << std::endl;
    }
    return *mMaps.find(map_id)->second;

}


void ResourceManager::loadMap(const mapID map_id, const std::string& filePath){

    Map map;
    map.load(filePath);

    if(mMaps.find(map_id) == mMaps.end()){


			mMaps.insert(std::make_pair( 
				map_id, 
				std::make_unique<Map>(std::move(map))  
			));


		}
}




void ResourceManager::play(const soundID sound_id){
	return sound_manager.play(sound_id);
}


void ResourceManager::removeTexture(const textureID texture_id){
	mTextures.erase(texture_id);
}

void ResourceManager::removeImage(const textureID image_id){
	mImages.erase(image_id);
}



