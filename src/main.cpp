#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include "../headers/3dEngine.h"



#if NDEBUG
int w = 1080;
int h = 720;
//int w = 1920;
//int h = 1080;
#else
int w = 640;
int h = 480;
#endif


int main(int argc, char* argv[]) {

    std::cout << "argv[0] = " << argv[0] << std::endl;

	Engine* engine = new Engine(w, h);


    try {

        int found = (std::string(argv[0]).find_last_of("/\\"));

        std::string path = std::string(argv[0]).substr(0, found);

        std::cout << std::endl << path + "\\..\\..\\res\\redbrick.png" << std::endl;

        //engine->loadTexture();
        engine->loadTexture(textureID::wallbrick, path + "/../../res/redbrick.png");
        engine->loadTexture(textureID::floor, path + "/../../res/colorstone.png");
        engine->loadTexture(textureID::prigojinTexture, path + "/../../res/prigojin.png");
        engine->loadTexture(textureID::barrelTexture, path + "/../../res/barrel.png");
        engine->loadTexture(textureID::pillar, path + "/../../res/pillar.png");
        engine->loadTexture(textureID::light, path + "/../../res/light.png");
        //engine->loadSprite();
        //engine->loadMap(world);
        //engine->loadImage();
        engine->loadMap(path + "/../../maps/map1.txt");
        //engine->loadThing();

        /*engine->loadEnemy({ 3,4 },0.8, textureID::prigojinTexture, 0, 1);
        engine->loadEnemy({ 10,6 },0.5, textureID::prigojinTexture, 0, 1);
        engine->loadEnemy({ 10,30 },0.7, textureID::prigojinTexture, 0, 1);
        engine->loadEnemy({ 3,22 },0.6, textureID::prigojinTexture, 0, 1);
        */engine->loadStaticObject({ 8,2 }, textureID::barrelTexture, 0, 0);
        engine->loadStaticObject({ 10,2 }, textureID::pillar, 0, 0);
        engine->loadStaticObject({ 14,2 }, textureID::light, 0, 0);

        engine->run();
    }
    catch (const char* ex) {
        std::cout << ex;
    }

	delete engine;
	return 0;

}

