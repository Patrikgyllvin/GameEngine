#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <iostream>
#include <iomanip>

#include <vector>

#include "Entity.h"

#include "../Events/EventManager.h"
#include "../Events/EntityEvent.h"

#include "../CoreComponents/Component.h"
#include "../../ComponentTypes.h"

namespace Engine
{
	class EntityManager
	{
	public:
		EntityManager( EventManager* eManager );
		~EntityManager();

		Entity& genEntity();
		void destroyEntity( Entity* entity );

	private:
		typedef std::vector< Entity* > EntityList;

		EventManager* eventManager;

		EntityID nextID;
	
		std::vector< unsigned int > usedIDs;
	
		EntityList entities;

		ComponentList components;
	};
}

#endif
