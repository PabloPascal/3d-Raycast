#include "../src/utils/PathFinder.h"
#include "../src/World/map.h"
#include "Game.h"


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
    int found = (std::string(argv0).find_last_of("/\\"));
    std::string path = std::string(argv0).substr(0, found);
    unsigned int w = 900;
    unsigned int h = 600;
   
    std::cout << "path = " << path << std::endl;

    std::cout << "choose resolution: " << std::endl;
    std::cout << "1: 1920x1080" << std::endl;
    std::cout << "2: 1080x720" << std::endl;
    std::cout << "3: 900x600" << std::endl;

    unsigned int choose;

    std::cin >> choose;

    switch (choose)
    {
    case 1:
        w = 1880;
        h = 990;
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
    int found = (std::string(argv0).find_last_of("/\\"));
    std::string path = std::string(argv0).substr(0, found);

    
    std::cout << "path = " << path << std::endl;

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

	

    Game* game;
    std::cout << std::endl << "path: " << path << std::endl;
    try{
        game = new Game(sf::Vector2u(w,h), path);
        game->run();

    }catch(const char* ex){
        std::cerr << ex << std::endl;
    }

    delete game;


}


