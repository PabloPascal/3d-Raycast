#include "../headers/map.h"
#include <fstream>
#include <iostream>



void map::load(int** world, int world_width, int world_height) {

	init(world_width, world_height);

	for (int i = 0; i < world_width; i++) {
		for (int j = 0; j < world_height; j++) {
			m_world[i][j] = world[i][j];
		}

	}

}



void map::load(std::vector<std::vector<int>> world) {

	init(world.size(), world[0].size());

	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			m_world[i][j] = world[i][j];
		}

	}

}



void map::load(std::string path) {

	std::ifstream map_file(path);

	if (!map_file.is_open()) {
		std::cerr << "can't open the file" << std::endl; 
		return;
	}
	map_file >> size_x;
	map_file >> size_y;

	init(size_x, size_y);

	for (int y = 0; y < size_y; y++) {
		for (int x = 0; x < size_x; x++) {
			map_file >> m_world[y][x];
		}
	}


	map_file.close();
}


void map::init(int world_width, int world_height) {

	size_x = world_width;
	size_y = world_height;

	m_world.resize(size_y);
	for (int i = 0; i < size_y; i++) {
		m_world[i].resize(size_x);
	}

}