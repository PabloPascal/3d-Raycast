#include "../src/utils/PathFinder.h"
#include "../src/World/map.h"
#include "Engine.h"


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
   
    std::cout << "choose resolution: " << std::endl;
    std::cout << "1: 1920x1080" << std::endl;
    std::cout << "2: 1080x720" << std::endl;
    std::cout << "3: 900x600" << std::endl;

    unsigned int choose;

    std::cin >> choose;

    switch (choose)
    {
    case 1:
        w = 1920;
        h = 1080;
        break;
    case 2:
        w = 1080;
        h = 720;
        break;
    case 3:
        w = 900;
        h = 600;
        break;
    default:
        break;
    }

    

#else
    int w = 900;
    int h = 600;
   
    std::cout << "choose resolution: " << std::endl;
    std::cout << "1: 1920x1080" << std::endl;
    std::cout << "2: 1080x720" << std::endl;
    std::cout << "3: 900x600" << std::endl;

    unsigned int choose;

    std::cin >> choose;

    switch (choose)
    {
    case 1:
        w = 1920;
        h = 1080;
        break;
    case 2:
        w = 1080;
        h = 720;
        break;
    case 3:
        w = 900;
        h = 600;
        break;
    default:
        break;
    }
#endif

	

    int found = (std::string(argv0).find_last_of("/\\"));
    std::string path = std::string(argv0).substr(0, found);
    std::cout << std::endl << path + "\\..\\..\\res\\redbrick.png" << std::endl;

    Engine* engine = new Engine(w, h, path);


    engine->loadMap(mapID::default_map ,"maps/map1.txt");
    //engine->loadThing();

    //engine->loadEnemy({ 5,2 },0.8, textureID::prigojinTexture, true, true, true);
    /*engine->loadEnemy({ 10,6 },0.5, textureID::prigojinTexture, 0, 1, 0, 0);
    engine->loadEnemy({ 10,30 },0.7, textureID::prigojinTexture, 0, 1);
    engine->loadEnemy({ 3,22 },0.6, textureID::prigojinTexture, 0, 1);*/
    engine->loadStaticObject({ 8,2 }, textureID::barrelTexture, 0, 0);
    engine->loadStaticObject({ 10,2 }, textureID::pillar, 0, 0);
    engine->loadStaticObject({ 14,2 }, textureID::light, 0, 0);

    engine->run();
    

	delete engine;


}


