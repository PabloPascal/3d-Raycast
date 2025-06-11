#include "../headers/map.h"


//map::map(int sizeX, int sizeY) {
//	size_x = sizeX;
//	size_y = sizeY;
//
//	m_world.resize(size_y);
//	for (int i = 0; i < size_y; i++) {
//		m_world[i].resize(size_x);
//	}
//
//}

void map::load(int** world, int world_width, int world_height) {

	size_x = world_width;
	size_y = world_height;

	for (int i = 0; i < world_width; i++) {
		for (int j = 0; j < world_height; j++) {
			m_world[i][j] = world[i][j];
		}

	}

}



void map::load(std::vector<std::vector<int>> world) {

	size_x = world.size();
	size_y = world[0].size();

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			m_world[i][j] = world[i][j];
		}

	}

}