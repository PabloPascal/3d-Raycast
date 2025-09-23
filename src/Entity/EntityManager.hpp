#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP


#include "defines.h"


#include <vector>



class EntityManager{
private:

    static EntityManager*   _instance; 

    std::vector<ThingPtr>   renderable_things;
    std::vector<EnemyPtr> 	enemies;
	std::vector<ObjectPtr> 	static_objects;


public:

    EntityManager() = default;
    EntityManager(const EntityManager& ) = delete;
    EntityManager& operator = (const EntityManager&) = delete;

    static EntityManager* getInstance();
    

    void loadAllGameObjects();

    void removeRenderableThing(const size_t index);

    std::vector<ThingPtr>& getVectorRenderables(); //return renderable_things
    std::vector<EnemyPtr>& 	getVectorEnemies();
    std::vector<ObjectPtr>& getVectorStaticsObj();


    ThingPtr& getRenderableThing(const size_t index);
    EnemyPtr& getEnemy(const size_t index);
    ObjectPtr& getStaticObject(const size_t index);

    void clearAll();
};



#endif 


