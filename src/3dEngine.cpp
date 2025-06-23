#include "../headers/3dEngine.h"

#include <iostream>
#include <string>

#if NDEBUG
#define FLOOR_TEX 1
#else 
#define FLOOR_TEX 1
#endif


Engine::Engine(size_t screen_width, size_t screen_hight)
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

		m_player->control(mMaps[0], sprites, timeSinceLastUpdate.asSeconds());

		renderer.render(m_window.getSize(), mMaps[0], m_player->getCamera(),
			mTextures.get(textureID::floor), mTextures.get(textureID::wallbrick), mTextures.get(textureID::spriteTexture), sprites);
		
		renderer.draw(m_window, mTextures.get(textureID::floor), mTextures.get(textureID::wallbrick), mTextures.get(textureID::spriteTexture));

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
	sf::Image image;
	image.loadFromFile("../res/prigojin.png");
	image.createMaskFromColor(sf::Color::Black);
	mTextures.load(textureID::spriteTexture, image);

}

void Engine::loadTexture(textureID id, const std::string& path) {

	mTextures.load(id, path);

}

void Engine::loadImage() {

}


void Engine::loadSprite() {

	sf::Sprite sprite;
	sprite.setPosition({ 2,10 });
	sprites.push_back(std::move(sprite));
}