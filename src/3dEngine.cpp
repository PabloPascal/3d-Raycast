#include "../headers/3dEngine.h"

#include <iostream>
#include <string>



Engine::Engine(size_t screen_width, size_t screen_hight) : Renderer(screen_width, screen_hight)
{
	m_window.create(sf::VideoMode(screen_width, screen_hight), "3d");
	m_player = std::make_unique<Player>(3.1415 / 3, 0, sf::Vector2f{1,2});
}



void Engine::run() {

	sf::Time timeSinceLastUpdate;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;


	while (m_window.isOpen()) {

		timeSinceLastUpdate = clock.restart();

		m_window.setTitle(std::to_string(1 / timeSinceLastUpdate.asSeconds()) + " FPS");

		sf::Event event;
		while (m_window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) m_window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					m_window.close();
			}

		}

		m_player->control(mMaps[0], things, timeSinceLastUpdate.asSeconds());

		for(auto& it: enemies)
			AI::simpleAI(it, m_player->getPos(), timeSinceLastUpdate.asSeconds());
		

		render(m_player->getCamera());

		m_window.display();

	}
}



void Engine::loadMap(const std::string& path) {

	Map map;
	map.load(path);
	mMaps.push_back(std::move(map));
}


void Engine::loadMap(Map& map) {

	mMaps.push_back(std::move(map));
}



void Engine::loadTexture() {

	mTextures.load(textureID::wallbrick, std::string("../res/redbrick.png"));
	mTextures.load(textureID::floor, std::string("../res/colorstone.png"));
	mTextures.load(textureID::barrelTexture, "../res/barrel.png");
	mTextures.load(textureID::prigojinTexture, "../res/prigojin.png");

}

void Engine::loadTexture(textureID id, const std::string& path) {

	mTextures.load(id, path);

}

void Engine::loadImage() {
	mImages.load(textureID::wallbrick, std::string("../res/redbrick.png"));
	mImages.load(textureID::floor, std::string("../res/colorstone.png"));
	mImages.load(textureID::barrelTexture, "../res/barrel.png");
	mImages.load(textureID::prigojinTexture, "../res/prigojin.png");
}


void Engine::loadSprite() {
}


void Engine::loadThing() {
	
	enemies.push_back(std::make_shared<Enemy>(sf::Vector2f{2,3},textureID::prigojinTexture, 0.5));
	numThings++;
	enemies.push_back(std::make_shared<Enemy>(sf::Vector2f{6,4}, textureID::prigojinTexture, 0.6));
	numThings++;
	enemies.push_back(std::make_shared<Enemy>(sf::Vector2f{10,5}, textureID::prigojinTexture, 0.8, 0, 1));
	numThings++;
	
	objects.push_back(std::make_shared<Object>(sf::Vector2f{ 8,2 }, textureID::barrelTexture, true));
	numThings++;


}



void Engine::loadEnemy(sf::Vector2f startPos,float speed, textureID tid, bool isCollsion, bool isAnimate) {

	enemies.push_back(std::make_shared<Enemy>(startPos, tid, speed, isCollsion, isAnimate));
	numThings++;
}


void Engine::loadStaticObject(sf::Vector2f startPos, textureID tid, bool isCollsion, bool isAnimate) {

	objects.push_back(std::make_shared<Object>(startPos, tid, isCollsion, isAnimate));
	numThings++;
}
