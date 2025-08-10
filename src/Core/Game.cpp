#include "Game.h"

#include <iostream>
#include <string>
#include <chrono>
#include "Demon.h"

Game::Game(const size_t screen_width,const size_t screen_height,const std::string& absolute_path) : Renderer(screen_width, screen_height)
{
	m_window.create(sf::VideoMode(screen_width, screen_height), "3d");
	m_player = std::make_unique<Player>( 5,sf::Vector2f{1,2});
	
	/*
	*	LOAD TEXUTRS
	*/

	mTextures.load(textureID::floor, absolute_path + "/res/colorstone.png");
	mTextures.load(textureID::prigojinTexture, absolute_path + "/res/prigojin.png");
	mTextures.load(textureID::barrelTexture, absolute_path + "/res/barrel.png");
	mTextures.load(textureID::pillar, absolute_path + "/res/pillar.png");
	mTextures.load(textureID::light, absolute_path + "/res/light.png");
	mTextures.load(textureID::wallTexture, absolute_path + "/res/walls_texture.png");
	mTextures.load(textureID::weapon, absolute_path + "/res/w0_b.png");
	mTextures.load(textureID::aim, absolute_path + "/res/aim.png");
	mTextures.load(textureID::monster_run1, absolute_path + "/res/monster_run1_0.png");
	mTextures.load(textureID::monster_run2, absolute_path + "/res/monster_run2_0.png");
	mTextures.load(textureID::monster_run3, absolute_path + "/res/monster_run3_0.png");
	/*
	*   LOAD IMAGES
	*/

	mImages.load(textureID::floor, absolute_path + "/res/colorstone.png");
	mImages.load(textureID::prigojinTexture, absolute_path + "/res/prigojin.png");
	mImages.load(textureID::barrelTexture, absolute_path + "/res/barrel.png");
	mImages.load(textureID::pillar,  absolute_path + "/res/pillar.png");
	mImages.load(textureID::light, absolute_path + "/res/light.png");
	mImages.load(textureID::wallTexture, absolute_path + "/res/greystone.png");;


	/*
	*   SET SPRITE
	*/

	weaponSprite.setTexture(mTextures.get(textureID::weapon));
	weaponSprite.setOrigin(sf::Vector2f(mTextures.get(textureID::weapon).getSize()));
	weaponSprite.scale({ 2 * (float)screen_width / 900.f, 2 * (float)screen_height / 600});
	weaponSprite.setPosition(sf::Vector2f(screen_width, screen_height + 20));
	
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

	weapon = std::make_unique<Weapon>(textureID::weapon);

	m_window.setMouseCursorVisible(false);

	/*
	* LOADD MAP
	*/
	Map map;
	map.load(absolute_path + "/maps/map2.txt");
	mMap.insert(std::make_pair(mapID::default_map, std::move(map)));


	/*
	* 	LOAD ENEMY
	*/
	std::shared_ptr<Demon> demon = std::make_shared<Demon>( Demon({3,3}, textureID::monster_run1, 2, true, true, true)  );
	demon->add_animations(textureID::monster_run1);
	demon->add_animations(textureID::monster_run2);
	demon->add_animations(textureID::monster_run3);


	renderable_things.push_back(demon);
	
	
	enemies.push_back(demon);
	/*
		sf::Vector2f position, textureID texture_id, 
        float speed, bool isCollision = false, 
		bool isAnimate = false, bool AIactivate = false
	*/
	

}



void Game::run() {

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;

	
	float deltaTime;
	while (m_window.isOpen()) {



		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;



			timeSinceLastUpdate = clock.restart();

			deltaTime = TimePerFrame.asSeconds();


			//m_window.setTitle(std::to_string(1 / timeSinceLastUpdate.asSeconds()) + " FPS");

			sf::Event event;
			while (m_window.pollEvent(event)) {

				if (event.type == sf::Event::Closed) m_window.close();
				if (event.type == sf::Event::KeyPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						m_window.close();
				}

			}

			m_player->update(mMap[mapID::default_map], renderable_things, m_window, deltaTime);



			for (auto& enemy : enemies) {
				enemy->update(*m_player.get(), mMap[mapID::default_map], deltaTime);
			}

			m_window.clear();

			render(m_player->getCamera());
			m_player->hand(weapon, m_window, weaponSprite, deltaTime);
			m_window.draw(aim);


			m_window.display();

		}

	}
}


