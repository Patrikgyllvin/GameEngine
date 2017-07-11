#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <iostream>
#include <iomanip>

#include <vector>

#include "../Events/EventManager.h"
#include "../Events/EntityEvent.h"

#include "../CoreComponents/Component.h"
#include "../../ComponentTypes.h"

namespace Engine
{
    class System;
    
    typedef unsigned int EntityID;
    
	class EntityManager
	{
	public:
		EntityManager( EventManager* eManager );
		~EntityManager();

		Entity& genEntity();
		void destroyEntity( Entity* entity );
        
        void registerSystem( System* system );
        void update();

	private:
		typedef std::vector< Entity* > EntityList;
        typedef std::vector< System* > SystemList;

		EventManager* eventManager;

		EntityID nextID;
	
		std::vector< unsigned int > usedIDs;
	
		EntityList entities;
        SystemList systems;
	};
}

#endif
