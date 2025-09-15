#include "Game.h"

#include <iostream>
#include <string>
#include <chrono>
#include "Demon.h"


Game::Game(const size_t screen_width,const size_t screen_height, 
		   const std::string& absolute_path)
{

	m_resources = ResourceManager::getInstance();
	m_EntityManager = EntityManager::getInstance();

	m_window.create(sf::VideoMode(screen_width, screen_height), "3d");

	m_renderer = new Renderer(m_window);

	m_player = std::make_unique<Player>( 5,sf::Vector2f{1,2});
	

	/*
									LOAD TEXUTRS
	*/


	m_resources->loadTexture(textureID::floor, absolute_path + "/res/colorstone.png");
	m_resources->loadTexture(textureID::prigojinTexture, absolute_path + "/res/prigojin.png");
	m_resources->loadTexture(textureID::barrelTexture, absolute_path + "/res/barrel.png");
	m_resources->loadTexture(textureID::pillar, absolute_path + "/res/pillar.png");
	m_resources->loadTexture(textureID::light, absolute_path + "/res/light.png");
	m_resources->loadTexture(textureID::wallTexture, absolute_path + "/res/walls_texture.png");


	m_resources->loadTexture(textureID::weapon, absolute_path + "/res/weapon.png");
	m_resources->loadTexture(textureID::weapon_fire1, absolute_path + "/res/weapon_fire1.png");
	m_resources->loadTexture(textureID::weapon_fire2, absolute_path + "/res/weapon_fire2.png");
	m_resources->loadTexture(textureID::weapon_fire3, absolute_path + "/res/weapon_fire3.png");


	m_resources->loadTexture(textureID::aim, absolute_path + "/res/aim.png");
	m_resources->loadTexture(textureID::monster_run1, absolute_path + "/res/monster_run1_0.png");
	m_resources->loadTexture(textureID::monster_run2, absolute_path + "/res/monster_run2_0.png");
	m_resources->loadTexture(textureID::monster_run3, absolute_path + "/res/monster_run3_0.png");


	/*
									LOAD IMAGES
	*/

	m_resources->loadImage(textureID::floor, absolute_path + "/res/colorstone.png");
	m_resources->loadImage(textureID::prigojinTexture, absolute_path + "/res/prigojin.png");
	m_resources->loadImage(textureID::barrelTexture, absolute_path + "/res/barrel.png");
	m_resources->loadImage(textureID::pillar,  absolute_path + "/res/pillar.png");
	m_resources->loadImage(textureID::light, absolute_path + "/res/light.png");
	m_resources->loadImage(textureID::wallTexture, absolute_path + "/res/greystone.png");


	/*		
									Init WallHeaderInfo
	*/

	wallSpriteInfo.m_id = textureID::wallTexture;
	wallSpriteInfo.texture_width = m_resources->getImage(textureID::wallTexture).getSize().x;
	wallSpriteInfo.texture_height = m_resources->getImage(textureID::wallTexture).getSize().y;
	wallSpriteInfo.offset = 64;
	wallSpriteInfo.sprite_count = 8;

	
	/*
									SET SPRITE
	*/

	weaponSprite.setTexture(m_resources->getTexture(textureID::weapon));
	weaponSprite.setOrigin(sf::Vector2f(m_resources->getTexture(textureID::weapon).getSize()));
	weaponSprite.scale({ 2 * (float)screen_width / 500.f, 2 * (float)screen_height / 500});
	weaponSprite.setPosition(sf::Vector2f(screen_width / 2.f + 250, screen_height + 20));
	

	aim.setTexture(m_resources->getTexture(textureID::aim));
	aim.setTextureRect(sf::IntRect({0,0}, {16,16}));
	aim.setOrigin(m_resources->getTexture(textureID::aim).getSize().x/2, m_resources->getTexture(textureID::aim).getSize().y / 2);
	aim.setPosition(screen_width / 2, screen_height / 2);
	aim.setScale({ 1.9, 1.9 });


	weapon = std::make_unique<Shotgun>(textureID::weapon, soundID::shotgun_fire_sound);
	weapon->load_animation(textureID::weapon);
	weapon->load_animation(textureID::weapon_fire1);
	weapon->load_animation(textureID::weapon_fire2);
	weapon->load_animation(textureID::weapon_fire3);
	weapon->setCooldownTime(1000);

	m_window.setMouseCursorVisible(false);

	/*
										LOAD MAP
	*/

	m_resources->loadMap(mapID::default_map, absolute_path + "/maps/map1.txt");
	


	/*
									 	LOAD GAME OBJECT
	*/

	m_EntityManager->loadAllGameObjects();

	/*
										LOAD SOUNDS
	*/

	m_resources->loadSound(soundID::shotgun_fire_sound, absolute_path + "/res/Shotgun_fire.wav");


}



void Game::run() {

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;

	sf::Clock timer;

	float deltaTime;


	while (m_window.isOpen()) {



		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			timeSinceLastUpdate = clock.restart();
			deltaTime = TimePerFrame.asSeconds();


			m_window.setTitle(std::to_string(1 / timeSinceLastUpdate.asSeconds()) + " FPS");

			sf::Event event;
			while (m_window.pollEvent(event)) {

				if (event.type == sf::Event::Closed) m_window.close();
				if (event.type == sf::Event::KeyPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						m_window.close();
				}

			}

			m_player->update(m_resources->getMap(mapID::default_map), m_EntityManager->getVectorRenderables(), m_window, deltaTime);


			for (auto& enemy : m_EntityManager->getVectorEnemies()) {
				enemy->update(*m_player.get(), m_resources->getMap(mapID::default_map), deltaTime);
			}

			m_window.clear();

			m_renderer -> render(m_player->getCamera(), wallSpriteInfo);
			m_player   -> hand(weapon.get(), m_window, weaponSprite, deltaTime);
			m_window.	  draw(aim);
			

			weapon->update(deltaTime);

			weaponSprite.setTexture(m_resources->getTexture(weapon->getTextureId()));

			m_window.display();

		}

	}
}


