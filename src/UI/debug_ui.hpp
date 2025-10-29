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

    DebugUI()
    {
        player.setRadius(20);
        player.setOrigin(20, 20);
        player.setFillColor(sf::Color::Magenta);
        enemy.setRadius(20);
        enemy.setOrigin(20,20);
        enemy.setFillColor(sf::Color::Red);

        CELL_SIZE = 40;
        
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