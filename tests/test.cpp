#include "../src/utils/PathFinder.h"
#include "../src/World/map.h"
#include "3dEngine.h"


#include <iostream>

static void printWorld(const Map& map) {
	for (auto i : map.m_world) {
		for (auto j : i)
			std::cout << j << " ";
		std::cout << std::endl;
	}
}

static void test1() {

	//Map map;
	//map.load("../maps/map1.txt");
	//printWorld(map);
	
	
	//PathFinder pf(map);

	//std::vector<Node> res = pf.getPath({ 1,1 }, { 4,4 });	
	
	/*for (auto i : res) {
		std::cout << " (" << i.first << ", " << i.second << ") " << std::endl;
	}*/

}



static void testEngine(char* argv0) {
#if NDEBUG
    int w = 900;
    int h = 600;
    /*int w = 1920;
    int h = 1080;*/
#else
    int w = 900;
    int h = 600;
#endif

	
	Engine* engine = new Engine(w, h);

    int found = (std::string(argv0).find_last_of("/\\"));
    std::string path = std::string(argv0).substr(0, found);
    std::cout << std::endl << path + "\\..\\..\\res\\redbrick.png" << std::endl;



    //engine->loadTexture();
    engine->loadTexture(textureID::wallbrick, path + "/../../res/redbrick.png");
    engine->loadTexture(textureID::floor, path + "/../../res/colorstone.png");
    engine->loadTexture(textureID::prigojinTexture, path + "/../../res/prigojin.png");
    engine->loadTexture(textureID::barrelTexture, path + "/../../res/barrel.png");
    engine->loadTexture(textureID::pillar, path + "/../../res/pillar.png");
    engine->loadTexture(textureID::light, path + "/../../res/light.png");
    engine->loadTexture(textureID::wallGrayBrick, path + "/../../res/greystone.png");
    //engine->loadSprite();
    //engine->loadMap(world);
    engine->loadImage();
    engine->loadMap(path + "/../../maps/map1.txt");
    //engine->loadThing();

    engine->loadEnemy({ 3,4 },0.8, textureID::prigojinTexture, false, true, true);
    /*engine->loadEnemy({ 10,6 },0.5, textureID::prigojinTexture, 0, 1, 0, 0);
    engine->loadEnemy({ 10,30 },0.7, textureID::prigojinTexture, 0, 1);
    engine->loadEnemy({ 3,22 },0.6, textureID::prigojinTexture, 0, 1);*/
    engine->loadStaticObject({ 8,2 }, textureID::barrelTexture, 0, 0);
    engine->loadStaticObject({ 10,2 }, textureID::pillar, 0, 0);
    engine->loadStaticObject({ 14,2 }, textureID::light, 0, 0);

    engine->run();
    

	delete engine;


}


