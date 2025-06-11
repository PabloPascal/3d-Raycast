#pragma once
#include <string>
#include <unordered_map>

class ResourceHolder {

	std::unordered_map<std::string, std::string> MAP; //our game map

	static ResourceHolder* resourseHolder;

public:

	static ResourceHolder* getResourseHolder();

	//name is the key, (name of map)
	void load(std::string path, std::string name);
	
	std::string get(std::string path);
};