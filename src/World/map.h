#pragma once
#include <vector>
#include <string>

struct Map {
	int world_width;
	int world_height;

	std::vector<std::vector<int>> m_world;

	//map(int sizeX, int sizeY);
public:
	Map() = default;
	
	void load(int** world, int world_width, int world_height);
	void load(std::vector<std::vector<int>>& world);
	void load(std::vector<std::vector<int>>&& world);
	void load(std::string path);
	
	Map(const Map& map);

	void operator=(const Map& other);
	void operator=(Map&& other) noexcept;

	int getMapCell(float x, float y) const;

private:
	void init(int world_width, int world_height);
};