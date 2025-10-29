#include "PathFinder.h"
#include <deque>



PathFinder::PathFinder(const Map& map) {
	
    for(int x = 0; x < map.world_width; x++){
        for(int y = 0; y < map.world_height; y++){

            if(map(x, y) == 0 ){

                Node node = {x,y};
                std::vector<Node> connect;

                for(auto to : dir){

                    int newX = node.first + to.first;
                    int newY = node.second + to.second;

                    if(newX < 0 || newX > map.world_width) continue;
                    if(newY < 0 || newY > map.world_height) continue;

                    if(map(newX, newY) == 0){
                        connect.push_back({newX, newY});
                    }

                }

                graph.insert(std::make_pair(node, connect));

            }

        }



    }



    // for(auto i : graph){
    //     int f1 = i.first.first;
    //     int f2 = i.first.second;

    //     std::cout << "{"<< f1 << ", " << f2 << "}, ";

    //     for(auto [x, y] : i.second){
    //         std::cout << "{x = " << x << ", y = " << y << "}, ";
    //     }
    //     std::cout << std::endl;
    // }

}


std::map<Node, std::optional<Node>> PathFinder::bfs(const Node& start, const Node& end) {

    std::map<Node, std::optional<Node>> visited;
    visited.insert(std::make_pair(start, std::nullopt));


    std::deque<Node> deq{start};
    while(!deq.empty()){

        Node currentNode = deq.front();
        deq.pop_front();

        if(currentNode == end) break;

        auto child = graph[currentNode];
        for(auto& nextNode: child)
        {   
            
            if(!visited.count(nextNode)){

                visited[nextNode] = currentNode;
                deq.push_back(nextNode);

            }
        }

    }

    return visited;

}



std::vector<Node> PathFinder::getPath(const Node& start, const Node& end) {

	auto visited = bfs(start, end);
    std::vector<Node> path = {end};

    
	std::optional<Node> step = start;
    if(visited.count(end)) step = end;
    step = visited[*step];

    while(step && step != start){

        path.push_back(*step);
        step = visited[*step];

    }


    return path;

}