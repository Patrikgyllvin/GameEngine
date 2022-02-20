#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <iostream>
#include <iomanip>

#include <vector>
#include <queue>

#include "../Events/EventManager.h"
#include "../Events/EntityEvent.h"

#include "../CoreComponents/Component.h"
#include "../../ComponentTypes.h"

namespace Engine
{
    class System;
    class RenderingSystem;

    typedef unsigned int EntityID;

	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		Entity& genEntity();
		void destroyEntity( Entity* entity );

        void registerSystem( System* system );
        void registerRenderingSystem( RenderingSystem* system );

        void init();
        void update();
        void render();

	private:
		typedef std::vector< Entity* > EntityList;
        typedef std::vector< System* > SystemList;
        typedef std::vector< RenderingSystem* > RenderingSystemList;

		EventManager eventManager;

		EntityID nextID;

		std::queue< unsigned int > usedIDs;

        std::queue< Entity* > toBeAdded;
        std::queue< Entity* > toBeRemoved;

		EntityList entities;
        SystemList systems;
        RenderingSystemList renderingSystems;
	};
}

#endif
