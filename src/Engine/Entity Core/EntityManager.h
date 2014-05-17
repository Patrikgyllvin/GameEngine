#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <iostream>
#include <iomanip>

#include <vector>

#include "EventManager.h"
#include "EntityEvent.h"

#include "Entity.h"

#include "Core Components/Component.h"
#include "ComponentTypes.h"

class EntityManager
{
public:
	EntityManager( EventManager* eManager );
	~EntityManager();
	
	Entity* genEntity();
	void destroyEntity( Entity* entity );

	Component* addComponent( Entity* entity, Component* comp );
	void destroyFirstComponent( Entity* entity, ComponentType compType );

	void destroyAllComponents( Entity* entity );

	const std::vector< Component* >& getComponentList( Entity* entity, ComponentType compType );

private:
	typedef std::vector< Entity* > EntityList;
	
	static const std::vector< Component* > emptyVec;

	EventManager* eventManager;

	EntityID nextID;

	std::vector< unsigned int > usedIDs;

	EntityList entities;
	std::vector< std::vector< std::vector< Component* > > > components;
};

#endif
