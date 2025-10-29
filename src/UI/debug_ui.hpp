#ifndef DEBUG_UI_HPP
#define DEBUG_UI_HPP


#include "map.h"
#include "PathFinder.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"

class DebugUI
{
private:

    int CELL_SIZE;
    int MAZE_WIDTH;
    int MAZE_HEIGHT;
    PathFinder* pf;
    sf::CircleShape player;
    sf::CircleShape enemy;
    

public:

    DebugUI(int screen_w, int screen_h)
    {
        player.setRadius(10);
        player.setOrigin(10, 10);
        player.setFillColor(sf::Color::Magenta);
        enemy.setRadius(10);
        enemy.setOrigin(10,10);
        enemy.setFillColor(sf::Color::Red);

        float max_screen_w = 1920;
        float max_screen_h = 1080;

        CELL_SIZE = 40 / max_screen_w * screen_w;
        
        MAZE_WIDTH = ResourceManager::getInstance()->getMap(mapID::default_map).world_width;
        MAZE_HEIGHT = ResourceManager::getInstance()->getMap(mapID::default_map).world_height;
        pf = new PathFinder(ResourceManager::getInstance()->getMap(mapID::default_map));
    }

    void visual_path_find_algorithm(sf::Vector2f player_pos, sf::Vector2f enemy_pos, sf::RenderTarget& window)
    {

        player.setPosition((player_pos) * (float)CELL_SIZE);
        enemy.setPosition((enemy_pos ) * (float)CELL_SIZE);

        std::vector<Node> path = pf->getPath({ (int)(enemy_pos.y  ), (int)(enemy_pos.x  ) },
                                             {(int)(player_pos.y ),(int)(player_pos.x )});

        for (int i = 0; i < MAZE_HEIGHT; i++) {
            for (int j = 0; j < MAZE_WIDTH; j++) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                
                if (ResourceManager::getInstance()->getMap(mapID::default_map)(i, j) > 0) {
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

        window.draw(player);
        window.draw(enemy);

    }

};



#endif