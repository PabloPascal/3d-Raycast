#pragma once


#include <iostream>
#include <map>
#include <vector>
#include <optional>
#include <deque>

#include "map.h"



using Node = std::pair<int, int>;

class PathFinder {

private:
	std::map<Node, std::vector<Node>> graph;

	Node dir[8] = { 
		{0,1}, 
		{0,-1}, 
		{1,0}, 
		{-1,0}, 
		{1,1}, 
		{-1,1}, 
		{-1,1}, 
		{1,-1}
	};

public:

	//PathFinder(const Map& map);
	
	//std::map<Node, std::optional<Node>> bfs(const Node& start, const Node& end);

	//std::vector<Node> getPath(const Node& start,const Node& end);
};