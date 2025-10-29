#include "../src/utils/PathFinder.h"
#include "../src/World/map.h"
#include "../src/utils/thread_pool.hpp"
#include <chrono>
#include <thread>
#include "Game.h"
#include "MathLib.h"

#include <iostream>
#include <exception>


static void printWorld(const Map& map) {
	for (auto i : map.m_world) {
		for (auto j : i)
			std::cout << j << " ";
		std::cout << std::endl;
	}
}

static void TESTpathFind() {

	Map map;
	map.load("../res/maps/map4.txt");
	printWorld(map);
	
	
	PathFinder pf(map);

	std::vector<Node> res = pf.getPath({ 1,1 }, { 6,8 });	

	for (auto& [x, y] : res) {
		std::cout << " (" << x << ", " << y << ") " << std::endl;
	}


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




static void thread_pool_test()
{

    auto lamd = [] { std::cout << "lamd()\n"; };

    try{
        ThreadPool thread_pool(4);
        thread_pool.add_task(lamd);
    }catch(std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}




static void visual_path_find_algorithm()
{

    Map maze;
	maze.load("../res/maps/map1.txt");

    const int CELL_SIZE = 40;
    const int MAZE_WIDTH = maze.world_width;
    const int MAZE_HEIGHT = maze.world_height;


//     std::vector<std::vector<int>> maze = {
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
//     {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
//     {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
//     {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
//     {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// };

    PathFinder pf(maze);

    sf::CircleShape enemy(20);
    enemy.setOrigin(20,20);
    enemy.setFillColor(sf::Color::Red);

    sf::CircleShape player(20);
    player.setOrigin(20,20);
    player.setFillColor(sf::Color::Red);

    float speed = 150;

    sf::Vector2f pos = {40 + 20, 40 + 20};
    enemy.setPosition(pos);

    sf::Vector2f player_pos = {40 * 10 + 20, 40 * 10 + 20};
    player.setPosition(player_pos);
    

    // Создание окна
    sf::RenderWindow window(
        sf::VideoMode(MAZE_WIDTH * CELL_SIZE, MAZE_HEIGHT * CELL_SIZE), 
        "Maze"
    );

    sf::Clock timer;
    float dt = 0;    

    while (window.isOpen()) {
        
        sf::Time time = timer.restart();
        dt = time.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if(maze((player_pos.y - speed * dt) / CELL_SIZE - 0.5, player_pos.x / CELL_SIZE) == 0)
            {
                player_pos.y -= speed * dt;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if(maze((player_pos.y + speed * dt) / CELL_SIZE + 0.5, player_pos.x / CELL_SIZE) == 0)
            {
                player_pos.y += speed * dt;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if(maze(player_pos.y / CELL_SIZE, (player_pos.x - speed * dt) / CELL_SIZE - 0.5) == 0)
            {
                player_pos.x -= speed * dt;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if(maze(player_pos.y / CELL_SIZE, (player_pos.x + speed * dt) / CELL_SIZE + 0.5) == 0)
            {
                player_pos.x += speed * dt;
            }
        }

        player.setPosition(player_pos);
        std::cout << "pos.x = " << pos.x << ", pos.y = " << pos.y << std::endl;

        pos = enemy.getPosition();
        std::vector<Node> path = pf.getPath({ (int)(pos.y / (CELL_SIZE) ), (int)(pos.x / (CELL_SIZE) ) },
                                             {(int)(player_pos.y / (CELL_SIZE)),(int)(player_pos.x / CELL_SIZE)});
        size_t size = path.size()-1;
        sf::Vector2f dir = sf::Vector2f(path[size].second + 0.5, path[size].first + 0.5) * (float)CELL_SIZE - pos;
    
        dir = dir / myMATH::VectorLen(dir);
        //std::cout << "dir.x = " << dir.x << ", dir.y = " << dir.y << std::endl;

        sf::Vector2f newPos = pos + dir * speed * dt;
        int cell_x = newPos.x / CELL_SIZE;
        int cell_y = newPos.y / CELL_SIZE;

        std::cout << "cell.x = " << cell_x << ",cell.y = " << cell_y << std::endl;
        if(myMATH::scalarProd(dir, sf::Vector2f(0,1)) > 0){

            if(maze( (pos + dir * speed*dt).y / CELL_SIZE + 0.5, pos.x / CELL_SIZE) == 0)
            {
                pos = {pos.x, (pos + dir * speed*dt).y};
                enemy.setPosition(pos);
            }

        }
        if(myMATH::scalarProd(dir, sf::Vector2f(0,1)) < 0){

            if(maze( (pos + dir * speed*dt).y / CELL_SIZE - 0.5, pos.x / CELL_SIZE) == 0)
            {
                pos = {pos.x, (pos + dir * speed*dt).y};
                enemy.setPosition(pos);
            }

        }

        if(myMATH::scalarProd(dir, sf::Vector2f(1,0)) > 0){
            if(maze( pos.y / CELL_SIZE, (pos + dir * speed*dt).x / CELL_SIZE + 0.5) == 0)
            {
                pos = {(pos + dir*speed*dt).x, pos.y};
                enemy.setPosition(pos);
            }
        }
        if(myMATH::scalarProd(dir, sf::Vector2f(1,0)) < 0){
            if(maze( pos.y / CELL_SIZE, (pos + dir * speed*dt).x / CELL_SIZE - 0.5) == 0)
            {
                pos = {(pos + dir*speed*dt).x, pos.y};
                enemy.setPosition(pos);
            }
        }
        


        // Отрисовка лабиринта
        for (int i = 0; i < MAZE_HEIGHT; i++) {
            for (int j = 0; j < MAZE_WIDTH; j++) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                
                if (maze(i, j) > 0) {
                    cell.setFillColor(sf::Color::Black); // Стена
                }
                else {
                    cell.setFillColor(sf::Color::White); // Проход
                    if(std::find(path.begin(), path.end(), Node(i,j)) != path.end())
                    {
                        cell.setFillColor(sf::Color::Green); // path
                    }
                }
                
                // Добавляем контур для лучшей видимости
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color(150, 150, 150));
                
                window.draw(cell);
            }
        }


        window.draw(enemy);
        window.draw(player);


        window.display();
        //std::this_thread::sleep_for(std::chrono::seconds(1));

    }



}
