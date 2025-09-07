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

	mTextures.load(textureID::weapon, absolute_path + "/res/weapon.png");
	mTextures.load(textureID::weapon_fire1, absolute_path + "/res/weapon_fire1.png");
	mTextures.load(textureID::weapon_fire2, absolute_path + "/res/weapon_fire2.png");
	mTextures.load(textureID::weapon_fire3, absolute_path + "/res/weapon_fire3.png");

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
	weaponSprite.scale({ 2 * (float)screen_width / 500.f, 2 * (float)screen_height / 500});
	weaponSprite.setPosition(sf::Vector2f(screen_width / 2.f + 250, screen_height + 20));
	

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

	weapon = std::make_unique<Shotgun>(textureID::weapon, soundID::shotgun_fire_sound);
	weapon->load_animation(textureID::weapon);
	weapon->load_animation(textureID::weapon_fire1);
	weapon->load_animation(textureID::weapon_fire2);
	weapon->load_animation(textureID::weapon_fire3);
	

	m_window.setMouseCursorVisible(false);

	/*
	* LOADD MAP
	*/
	Map map;
	map.load(absolute_path + "/maps/map3.txt");
	mMap.insert(std::make_pair(mapID::default_map, std::move(map)));


	/*
	* 	LOAD ENEMY
	*/
	std::shared_ptr<Demon> demon1 = std::make_shared<Demon>( Demon({3,3}, textureID::monster_run1, 2, true, true, true)  );

	demon1->set_animations(textureID::monster_run1);
	demon1->set_animations(textureID::monster_run2);
	demon1->set_animations(textureID::monster_run3);

	renderable_things.push_back(demon1);
	enemies.push_back(demon1);


	/*
	*	LOAD STATIC SPRITE 
	*/

	renderable_things.push_back(std::move(std::make_shared<StaticObject>(StaticObject({5,5}, textureID::barrelTexture, false, false) ) ));
	renderable_things.push_back(std::move(std::make_shared<StaticObject>(StaticObject({10,15}, textureID::pillar, false, false) ) ));
	renderable_things.push_back(std::move(std::make_shared<StaticObject>(StaticObject({20,5}, textureID::pillar, false, false) ) ));
	renderable_things.push_back(std::move(std::make_shared<StaticObject>(StaticObject({10,20}, textureID::light, false, false) ) ));


	/*
		====================SOUND============================
	*/

	sounds_.loadSound(soundID::shotgun_fire_sound, absolute_path + "/res/Shotgun_fire.wav");

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

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer.getElapsedTime().asMilliseconds() > 3000){
				sounds_.play(soundID::shotgun_fire_sound);
				timer.restart();
				std::cout << "MOUSE::LEFT\n";
			}

			for (auto& enemy : enemies) {
				enemy->update(*m_player.get(), mMap[mapID::default_map], deltaTime);
			}

			m_window.clear();

			render(m_player->getCamera());
			m_player->hand(weapon.get(), m_window, weaponSprite, deltaTime);
			m_window.draw(aim);
		

			weapon->update(deltaTime);

			weaponSprite.setTexture(mTextures.get(weapon->getTextureId()));

			m_window.display();

		}

	}
}


