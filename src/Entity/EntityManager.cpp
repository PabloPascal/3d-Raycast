#include "EntityManager.hpp"
#include "Demon.h"
#include "StaticObject.h"
#include "Thing.h"

#include <iostream>

EntityManager* EntityManager::_instance = nullptr;


EntityManager* EntityManager::getInstance(){

    if(_instance == nullptr){
        _instance = new EntityManager;
    }

    return _instance;
}


void EntityManager::loadAllGameObjects()
{

    //LOAD ENEMIES

    std::shared_ptr<Demon> demon1 = std::make_shared<Demon>( Demon({2,3}, textureID::monster_run1, 2, true, true, true)  );

	demon1->set_animations(textureID::monster_run1);
	demon1->set_animations(textureID::monster_run2);
	demon1->set_animations(textureID::monster_run3);


    renderable_things.push_back(demon1);
    enemies.push_back(demon1);

    //LOAD STATIC_OBJECT

    renderable_things.push_back(std::move(
        std::make_shared<StaticObject>(StaticObject({2,5}, textureID::barrelTexture, false, false) ) 
    ));

    renderable_things.push_back(std::move(
        std::make_shared<StaticObject>(StaticObject({2,8}, textureID::pillar, false, false) ) 
    ));

    renderable_things.push_back(std::move(
        std::make_shared<StaticObject>(StaticObject({8,2}, textureID::light, false, false) ) )
    );
}





void EntityManager::removeRenderableThing(const size_t index){

    if(index > renderable_things.size()){
        std::cerr << "index bigger than vector.size()" << std::endl;
        return;
    }
    renderable_things.erase(renderable_things.begin() + index);
}



void EntityManager::clearAll(){

    renderable_things.clear();
    
}




ThingPtr& EntityManager::getRenderableThing(const size_t index){
    return renderable_things[index];
}




EnemyPtr& EntityManager::getEnemy(const size_t index){
    return enemies[index];
}


ObjectPtr& EntityManager::getStaticObject(const size_t index){
    return static_objects[index];
}



std::vector<ThingPtr>& EntityManager::getVectorRenderables(){
    return renderable_things;
}

std::vector<EnemyPtr>& 	EntityManager::getVectorEnemies(){
    return enemies;
}

std::vector<ObjectPtr> EntityManager::getVectorStaticsObj(){
    return static_objects;
}