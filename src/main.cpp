#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include "../headers/3dEngine.h"


const float PI = 3.1415;




#if NDEBUG
int w = 1080;
int h = 720;
#else
int w = 900;
int h = 600;
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
        engine->loadTexture(textureID::spriteTexture, path + "/../../res/prigojin.png");
        //engine->loadTexture(textureID::spriteTexture, path + "/../../res/barrel.png");
        engine->loadSprite();
        //engine->loadMap(world);
        engine->loadMap(path + "/../../maps/map1.txt");

        engine->run();
    }
    catch (const char* ex) {
        std::cout << ex;
    }

	delete engine;
	return 0;

}

