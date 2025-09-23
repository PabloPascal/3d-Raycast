#include "Game.h"

#include <iostream>
#include <string>
#include <chrono>
#include "Demon.h"
#include "Pistol.hpp"
#include <algorithm>
#include <iterator>


Game::Game(const size_t screen_width,const size_t screen_height, 
		   const std::string& absolute_path)
{

	m_resources = ResourceManager::getInstance();
	m_EntityManager = EntityManager::getInstance();

	m_window.create(sf::VideoMode(screen_width, screen_height), "3d");

	m_renderer = new Renderer(m_window);

	g_camera = new Camera;
	g_camera->m_position = {2,2};
	m_player = std::make_unique<Player>( 5, g_camera);
	

	/*
									LOAD TEXTURES
	*/

	std::cout << "load textures: walls" << std::endl;

	//walls and props
	m_resources->loadTexture(textureID::floor, absolute_path + "/res/textures/walls and props/colorstone.png");
	m_resources->loadTexture(textureID::barrelTexture, absolute_path + "/res/textures/walls and props/barrel.png");
	m_resources->loadTexture(textureID::pillar, absolute_path + "/res/textures/walls and props/pillar.png");
	m_resources->loadTexture(textureID::light, absolute_path + "/res/textures/walls and props/light.png");
	m_resources->loadTexture(textureID::wallTexture, absolute_path + "/res/textures/walls and props/walls_texture.png");

	std::cout << "load textures: weapons" << std::endl;
	//weapon shorgun
	m_resources->loadTexture(textureID::weapon, absolute_path + "/res/textures/weapon/weapon.png");
	m_resources->loadTexture(textureID::weapon_fire1, absolute_path + "/res/textures/weapon/weapon_fire1.png");
	m_resources->loadTexture(textureID::weapon_fire2, absolute_path + "/res/textures/weapon/weapon_fire2.png");
	m_resources->loadTexture(textureID::weapon_fire3, absolute_path + "/res/textures/weapon/weapon_fire3.png");

	//weapon pistol
	m_resources->loadTexture(textureID::pistol_0, absolute_path + "/res/textures/weapon/PIST_1.png");
	m_resources->loadTexture(textureID::pistol_1, absolute_path + "/res/textures/weapon/PIST_2.png");
	m_resources->loadTexture(textureID::pistol_2, absolute_path + "/res/textures/weapon/PIST_3.png");
	m_resources->loadTexture(textureID::pistol_3, absolute_path + "/res/textures/weapon/PIST_4.png");

	//aim
	m_resources->loadTexture(textureID::aim, absolute_path + "/res/textures/weapon/aim.png");


	std::cout << "load textures: monsters" << std::endl;
	//monsters
	m_resources->loadTexture(textureID::monster_run1, absolute_path + "/res/textures/monsters/monster_run1_0.png");
	m_resources->loadTexture(textureID::monster_run2, absolute_path + "/res/textures/monsters/monster_run2_0.png");
	m_resources->loadTexture(textureID::monster_run3, absolute_path + "/res/textures/monsters/monster_run3_0.png");

	m_resources->loadTexture(textureID::monser_attack1, absolute_path + "/res/textures/monsters/monster_attack0_0.png");
	m_resources->loadTexture(textureID::monser_attack2, absolute_path + "/res/textures/monsters/monster_attack1_0.png");
	m_resources->loadTexture(textureID::monser_attack3, absolute_path + "/res/textures/monsters/monster_attack2_0.png");

	m_resources->loadTexture(textureID::monster_death1, absolute_path + "/res/textures/monsters/monster_death0.png");
	m_resources->loadTexture(textureID::monster_death2, absolute_path + "/res/textures/monsters/monster_death1.png");
	m_resources->loadTexture(textureID::monster_death3, absolute_path + "/res/textures/monsters/monster_death2.png");
	m_resources->loadTexture(textureID::monster_death4, absolute_path + "/res/textures/monsters/monster_death3.png");
	m_resources->loadTexture(textureID::monster_death5, absolute_path + "/res/textures/monsters/monster_death4.png");
	m_resources->loadTexture(textureID::monster_death6, absolute_path + "/res/textures/monsters/monster_death5.png");




	/*
									LOAD IMAGES
	*/
	std::cout << "load images: floor" << std::endl;

	m_resources->loadImage(textureID::floor, absolute_path + "/res/textures/walls and props/colorstone.png");
	m_resources->loadImage(textureID::wallTexture, absolute_path + "/res/textures/walls and props/walls_texture.png");


	/*		
									Init WallHeaderInfo
	*/

	std::cout << "init walls info" << std::endl;

	wallSpriteInfo.m_id = textureID::wallTexture;
	wallSpriteInfo.texture_width = m_resources->getImage(textureID::wallTexture).getSize().x;
	wallSpriteInfo.texture_height = m_resources->getImage(textureID::wallTexture).getSize().y;
	wallSpriteInfo.offset = 64;
	wallSpriteInfo.sprite_count = 8;

	std::cout << "set sprites" << std::endl;
	/*
									SET SPRITE
	*/

	weaponSprite.setTexture(m_resources->getTexture(textureID::weapon));
	weaponSprite.setOrigin(sf::Vector2f(m_resources->getTexture(textureID::weapon).getSize()));
	weaponSprite.scale({ 2 * (float)screen_width / 400.f, 2 * (float)screen_height / 300.f});
	sf::Vector2u tex_size = m_resources->getTexture(textureID::weapon).getSize();
	//weaponSprite.setPosition(sf::Vector2f(screen_width / 2.f + 2*tex_size.x, screen_height + 20));
	weaponSprite.setPosition(sf::Vector2f(screen_width, screen_height));
	

	aim.setTexture(m_resources->getTexture(textureID::aim));
	aim.setTextureRect(sf::IntRect({0,0}, {16,16}));
	aim.setOrigin(m_resources->getTexture(textureID::aim).getSize().x/2, m_resources->getTexture(textureID::aim).getSize().y / 2);
	aim.setPosition(screen_width / 2, screen_height / 2);
	aim.setScale({ 1.9, 1.9 });


	std::cout << "load shotgun" << std::endl;
	auto shotgun = std::make_unique<Shotgun>(textureID::weapon, soundID::shotgun_fire_sound);
	shotgun->load_animation(textureID::weapon);
	shotgun->load_animation(textureID::weapon_fire1);
	shotgun->load_animation(textureID::weapon_fire2);
	shotgun->load_animation(textureID::weapon_fire3);
	shotgun->setCooldownTime(1000);

	std::cout << "load pistol" << std::endl;
	auto pistol = std::make_unique<Pistol>(textureID::pistol_0, soundID::pistol_frie_sound);
	pistol->load_animation(textureID::pistol_0);
	pistol->load_animation(textureID::pistol_1);
	pistol->load_animation(textureID::pistol_2);
	pistol->load_animation(textureID::pistol_3);
	pistol->setCooldownTime(300);

	weapon = std::move(pistol);

	m_window.setMouseCursorVisible(false);

	/*
										LOAD MAP
	*/

	std::cout << "load map" << std::endl;
	m_resources->loadMap(mapID::default_map, absolute_path + "/res/maps/map2.txt");
	


	/*
									 	LOAD GAME OBJECT
	*/

	std::cout << "load all objects on world" << std::endl;
	m_EntityManager->loadAllGameObjects();

	/*
										LOAD SOUNDS
	*/

	std::cout << "load sounds" << std::endl;
	m_resources->loadSound(soundID::shotgun_fire_sound, absolute_path + "/res/sounds/Shotgun_fire.wav");
	m_resources->loadSound(soundID::pistol_frie_sound, absolute_path +  "/res/sounds/pistol-shot.wav");


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
			observe();

			for (auto& enemy : m_EntityManager->getVectorEnemies()) {
				enemy->update(*m_player.get(), m_resources->getMap(mapID::default_map), deltaTime);
			}

			m_window.clear();

			m_renderer -> render(*g_camera, wallSpriteInfo);
			m_player   -> hand(weapon.get(), m_window, weaponSprite, deltaTime);
			m_window.	  draw(aim);
			

			weapon->update(deltaTime);

			weaponSprite.setTexture(m_resources->getTexture(weapon->getTextureId()));

			m_window.display();

		}

	}
}




void Game::observe(){

	auto* enemies = &m_EntityManager->getVectorEnemies();
	auto* statics = &m_EntityManager->getVectorStaticsObj();
	auto* renderables = &m_EntityManager->getVectorRenderables();


	for(auto it = enemies->begin(); it != enemies->end(); ){
		if(!it->get()->isAlive()){
			it = enemies->erase(it);
		}
		else{
			++it;
		}
	}

	if(renderables->size() != enemies->size() + statics->size()){
		renderables->clear();
		std::copy(enemies->begin(), enemies->end(), std::back_inserter(*renderables));
	}

}

