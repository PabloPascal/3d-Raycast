#include "map.h"
#include <fstream>
#include <iostream>


Map::Map(const Map& map) {
	world_height = map.world_height;
	world_width = map.world_width;
	m_world = map.m_world;
}



void Map::load(int** world, int world_width, int world_height) {

	init(world_width, world_height);

	for (int i = 0; i < world_width; i++) {
		for (int j = 0; j < world_height; j++) {
			m_world[i][j] = world[i][j];
		}

	}

}



void Map::load(std::vector<std::vector<int>>& world) {

	init(world.size(), world[0].size());

	m_world = world;

}

void Map::load(std::vector<std::vector<int>>&& world) {

	init(world.size(), world[0].size());

	m_world = std::move(world);

}




void Map::load(std::string path) {

	std::ifstream map_file(path);

	if (!map_file.is_open()) {
		std::cerr << "can't open the file" << std::endl; 
		return;
	}
	map_file >> world_width;
	map_file >> world_height;

	init(world_width, world_height);

	for (int y = 0; y < world_height; y++) {
		for (int x = 0; x < world_width; x++) {
			map_file >> m_world[y][x];
		}
	}


	map_file.close();
}


void Map::init(int width, int height) {

	world_width = width;
	world_height = height;

	m_world.resize(world_height);
	for (int i = 0; i < world_height; i++) {
		m_world[i].resize(world_width);
	}

}




void Map::operator=(const Map& other) {
	m_world = other.m_world;
	world_width = other.world_width;
	world_height = other.world_height;
}


void Map::operator=(Map&& other) noexcept
{
	m_world = std::move(other.m_world);
	world_width = other.world_width;
	world_height = other.world_height;

}