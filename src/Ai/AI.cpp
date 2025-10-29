#include "AI.h"
#include <cmath>
#include "MathLib.h"


PathFinder* AI::pf = nullptr;
bool AI::inited = false;


void AI::pathFindAlgorithm(Enemy* enemy, Player& player, const Map& map, float dt) {

	if(!inited){
		init(map);
		inited = true;
	}

	float speed = enemy->getSpeed();

	sf::Vector2i IenemyPos = {(int)(enemy->getPosition().x), (int)(enemy->getPosition().y)};
	sf::Vector2i IplayerPos = {(int)player.getPos().x, (int)player.getPos().y};

	Node start = {IenemyPos.y, IenemyPos.x};
	Node end = {IplayerPos.y, IplayerPos.x};

	std::vector<Node> path = AI::pf->getPath( start, end);
	
	int last = path.size() - 1;
	auto [x, y] = path[last];

	sf::Vector2f dir = sf::Vector2f((float)y + 0.5, (float)x + 0.5) - enemy->getPosition();


	PhysicsEngine::EnemyCollisionResolver(enemy, map, dir * speed*dt);


	if(myMATH::VectorLen(enemy->getPosition() - player.getCamera()->m_position) < 1){
		enemy->attack(player);
	}


}


void AI::simpleEnemyAI(Enemy* enemy,Player& player,const Map& map, float dt){

	sf::Vector2f direction = player.getCamera()->m_position - enemy->getPosition();
	
	float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= dist;

	sf::Vector2f move = direction * enemy->getSpeed() * dt;
	sf::Vector2f newPos = enemy->getPosition() + move;

	PhysicsEngine::EnemyCollisionResolver(enemy, map, move);

	if(myMATH::VectorLen(enemy->getPosition() - player.getCamera()->m_position) < 1){
		enemy->attack(player);
	}


}