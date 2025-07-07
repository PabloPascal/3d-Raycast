//#include "PathFinder.h"
//
//
//
//PathFinder::PathFinder(const Map& map) {
//	for (int x = 0; x < map.world_width; x++) {
//		for (int y = 0; y < map.world_height; y++) {
//			
//			if (map.m_world[x][y] != 1) {
//				
//				std::vector<Node> nodes;
//				auto it = graph.find({ x,y });
//				
//				if (it != graph.end()) {
//					nodes = it->second;
//				}
//				
//				for (auto i : dir) {
//					int newX = x + i.first;
//					int newY = y + i.second;
//					if (map.m_world[newX][newY] != 1)
//						nodes.push_back({ newX, newY });
//				}
//
//				graph[{x, y}] = nodes;
//
//			}
//
//		}
//	}
//
//
//}
//
//
//std::map<Node, std::optional<Node>> PathFinder::bfs(const Node& start, const Node& end) {
//	std::map<Node, std::optional<Node>>  visited{
//		{start, std::nullopt}
//	};
//
//
//
//	std::deque<Node> queue{start};
//	while (!queue.empty()) {
//		Node currentNode = queue.front();
//		queue.pop_front();
//
//		if (currentNode == end) break;
//
//		for (auto& nextNode : graph[currentNode]) {
//			if (!visited.count(nextNode)) {
//				visited[nextNode] = currentNode;
//				queue.push_back(nextNode);
//			}
//		}
//
//	}
//
//	return visited;
//
//}
//
//
//
//std::vector<Node> PathFinder::getPath(const Node& start, const Node& end) {
//
//	auto visited = bfs(start, end);
//	std::vector<Node>  path{ end };
//	std::optional<Node> step = start;
//
//	if (visited.count(end)) step = visited.at(end);
//
//	while (step && step != start) {
//		path.push_back(*step);
//		step = visited[*step];
//	}
//
//	return path;
//	
//
//}