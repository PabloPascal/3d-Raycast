#include "../headers/ResourceHolder.h"
#include <fstream>
#include <iostream>
#include <sstream>

ResourceHolder* ResourceHolder::resourseHolder = nullptr;

ResourceHolder* ResourceHolder::getResourseHolder() {

	if (resourseHolder != nullptr) {
		return resourseHolder;
	}

	resourseHolder = new ResourceHolder;
	return resourseHolder;
}


void ResourceHolder::load(std::string path, std::string name) {

	if (MAP.find(name) == MAP.end()) {
		return;
	}

	std::ifstream file(path);

	if (!file.is_open()) {
		std::cerr << "can't open the file!\n";
		return;
	}

	std::stringstream map;

	map << file.rdbuf();

	file.close();

	MAP.insert(std::make_pair(name, map.str()));

}
