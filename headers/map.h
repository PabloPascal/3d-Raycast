#pragma once
#include <vector>

struct map {
	int size_x;
	int size_y;

	std::vector<std::vector<int>> m_world;

	//map(int sizeX, int sizeY);

	void load(int** world, int world_width, int world_height);
	void load(std::vector<std::vector<int>> world);

};