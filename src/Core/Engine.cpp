#include "Engine.h"

#include <iostream>
#include <string>



Engine::Engine(const size_t screen_width,const size_t screen_height,const std::string& absolute_path) : Renderer(screen_width, screen_height)
{
	m_window.create(sf::VideoMode(screen_width, screen_height), "3d");
	m_player = std::make_unique<Player>(3.1415 / 3, 0, sf::Vector2f{1,2});

	/*
	*	LOAD TEXUTRS
	*/

	mTextures.load(textureID::floor, absolute_path + "/../../res/colorstone.png");
	mTextures.load(textureID::prigojinTexture, absolute_path + "/../../res/prigojin.png");
	mTextures.load(textureID::barrelTexture, absolute_path + "/../../res/barrel.png");
	mTextures.load(textureID::pillar, absolute_path + "/../../res/pillar.png");
	mTextures.load(textureID::light, absolute_path + "/../../res/light.png");
	mTextures.load(textureID::wallTexture, absolute_path + "/../../res/walls_texture.png");
	mTextures.load(textureID::weapon, absolute_path + "/../../res/w0_b.png");
	mTextures.load(textureID::aim, absolute_path + "/../../res/aim.png");
	
	/*
	*   LOAD IMAGES
	*/

	mImages.load(textureID::floor, absolute_path + "/../../res/colorstone.png");
	mImages.load(textureID::prigojinTexture, absolute_path + "/../../res/prigojin.png");
	mImages.load(textureID::barrelTexture, absolute_path + "/../../res/barrel.png");
	mImages.load(textureID::pillar, absolute_path + "/../../res/pillar.png");
	mImages.load(textureID::light, absolute_path + "/../../res/light.png");
	mImages.load(textureID::wallTexture, absolute_path + "/../../res/greystone.png");;


	/*
	*   SET SPRITE
	*/

	weaponSprite.setTexture(mTextures.get(textureID::weapon));
	weaponSprite.setOrigin(sf::Vector2f(mTextures.get(textureID::weapon).getSize()));
	weaponSprite.scale({ 2,2 });
	weaponSprite.setPosition(screen_width, screen_height + 20);
	
	aim.setTexture(mTextures.get(textureID::aim));
	aim.setTextureRect(sf::IntRect({0,0}, {16,16}));
	aim.setOrigin(mTextures.get(textureID::aim).getSize().x/2, mTextures.get(textureID::aim).getSize().y / 2);
	aim.setPosition(screen_width / 2, screen_height / 2);
	aim.setScale({ 1.9, 1.9 });

	/*		
		Init WallHeaderInfo
	*/

	wallSpriteInfo.m_id = textureID::wallTexture;
	wallSpriteInfo.texture_width = mTextures.get(textureID::wallTexture).getSize().x;
	wallSpriteInfo.texture_height = mTextures.get(textureID::wallTexture).getSize().y;
	wallSpriteInfo.offset = 64;
	wallSpriteInfo.sprite_count = 8;

	weapon = new Weapon(textureID::weapon);

}



void Engine::run() {

	sf::Time timeSinceLastUpdate;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;

	float deltaTime;
	while (m_window.isOpen()) {

		timeSinceLastUpdate = clock.restart();

		deltaTime = timeSinceLastUpdate.asSeconds();

		m_window.setTitle(std::to_string(1 / deltaTime) + " FPS");

		sf::Event event;
		while (m_window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) m_window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					m_window.close();
			}

		}

		m_player->control(mMap[mapID::default_map], things, deltaTime);

		

		for (auto& enemy : enemies) {
			AI::simpleAI(enemy, m_player->getPos(), deltaTime);
		}

		m_window.clear();

		render(m_player->getCamera());
		m_player->hand(weapon, m_window, weaponSprite, deltaTime);
		m_window.draw(aim);

		m_window.display();

	}
}



void Engine::loadMap(mapID map_id,const std::string& path) {

	Map map;
	map.load(path);
	mMap[map_id] = std::move(map);
}


void Engine::loadMap(mapID map_id,Map& map) {

	mMap[map_id] = std::move(map);
}



void Engine::loadTexture() {

	mTextures.load(textureID::wallTexture, std::string("../res/redbrick.png"));
	mTextures.load(textureID::floor, std::string("../res/colorstone.png"));
	mTextures.load(textureID::barrelTexture, "../res/barrel.png");
	mTextures.load(textureID::prigojinTexture, "../res/prigojin.png");

}

void Engine::loadTexture(textureID id, const std::string& path) {

	mTextures.load(id, path);

}

void Engine::loadImage() {
	mImages.load(textureID::wallTexture, std::string("../res/redbrick.png"));
	mImages.load(textureID::floor, std::string("../res/colorstone.png"));
	mImages.load(textureID::barrelTexture, "../res/barrel.png");
	mImages.load(textureID::prigojinTexture, "../res/prigojin.png");
}



void Engine::loadImage(textureID id, const std::string& path) {

	mImages.load(id, path);

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



void Engine::loadEnemy(sf::Vector2f startPos,float speed, textureID tid, bool isCollsion, bool isAnimate, bool AI) {

	enemies.push_back(std::make_shared<Enemy>(startPos, tid, speed, isCollsion, isAnimate, AI));
	numThings++;
}


void Engine::loadStaticObject(sf::Vector2f startPos, textureID tid, bool isCollsion, bool isAnimate) {

	objects.push_back(std::make_shared<Object>(startPos, tid, isCollsion, isAnimate));
	numThings++;
}
