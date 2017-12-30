#if !defined(__APPLE__) || defined(_MAC_MAKEFILE)
#include "../../../include/Engine/EntityCore/EntityManager.h"
#else
#include "EntityManager.h"
#include "Entity.h"
#include "System.h"
#include "RenderingSystem.h"
#endif



#include <ctime>

namespace Engine
{
	EntityManager::EntityManager( EventManager* eManager )
	:
	eventManager( eManager ),
	nextID( 0 ),
	usedIDs(),
	entities()
	{}

	EntityManager::~EntityManager()
	{
		for( std::vector< Entity* >::iterator it = entities.begin(); it != entities.end(); ++it )
			destroyEntity( *it );
        
        for( auto it = systems.begin(); it != systems.end(); ++it )
            delete *it;

		entities.clear();
	}

	Entity& EntityManager::genEntity()
	{
		EntityID id;

		if( !usedIDs.empty() )
		{
			id = usedIDs.front();
			usedIDs.pop();
		}
		else
		{
			id = nextID++;
		}
        
        std::cout << "Current ID: " << id << '\n';
        
        Entity* entity = new Entity( id, *this );
		
		if( id >= entities.size() )
        {
            // Add to queue, add entity later when there is time to resize.
            toBeAdded.push( entity );
        }
        else
        {
            entities[ id ] = entity;
        }
        
		// Notify systems
		eventManager->pushEvent( EntityEvent( EVENT_ENTITY_CREATED, entity ) );

		return *entity;
	}

	void EntityManager::destroyEntity( Entity* entity )
	{
        entities[ entity->getID() ] = nullptr;
        
		usedIDs.push( entity->getID() );

		entity->destroyAllComponents();
		
		// Notify systems
		eventManager->pushEvent( EntityEvent( EVENT_ENTITY_DESTROYED, entity ) );

		delete entity;
	}
    
    void EntityManager::registerSystem( System* system )
    {
        systems.push_back( system );
    }
    
    void EntityManager::registerRenderingSystem( RenderingSystem *system )
    {
        renderingSystems.push_back( system );
    }
    
    void EntityManager::init()
    {
        // Initialize all systems
        for( auto sIt = systems.begin(); sIt != systems.end(); ++sIt )
        {
            (*sIt)->initialize();
        }
        
        for( auto rSIt = renderingSystems.begin(); rSIt != renderingSystems.end(); ++rSIt )
        {
            (*rSIt)->initialize();
        }
    }
    
    void EntityManager::update()
    {
        // Add entities in queue
        entities.resize( toBeAdded.back()->getID() + 10, nullptr );
        
        while( !toBeAdded.empty() )
        {
            entities[ toBeAdded.front()->getID() ] = toBeAdded.front();
            
            toBeAdded.pop();
        }
        
        // Pre-process all systems...
        for( auto it = systems.begin(); it != systems.end(); ++it )
        {
            (*it)->update();
        }
        
        for( auto it = renderingSystems.begin(); it != renderingSystems.end(); ++it )
        {
            (*it)->update();
        }
        
        // Process all entities
        for( auto it = entities.begin(); it != entities.end(); ++it )
        {
            for( auto sIt = systems.begin(); sIt != systems.end(); ++sIt )
            {
                // Check if entity should be processed by any system. If so, do it
                if( *it != nullptr && (*sIt)->shouldProcessEntity( **it ) )
                {
                    (*sIt)->updateEntity( **it );
                }
            }
            
            for( auto rSIt = renderingSystems.begin(); rSIt != renderingSystems.end(); ++rSIt )
            {
                // Check if entity should be processed by the rendering system. If so, do it
                if( *it != nullptr && (*rSIt)->shouldProcessEntity( **it ) )
                {
                    (*rSIt)->updateEntity( **it );
                }
            }
        }
    }
    
    void EntityManager::render()
    {
        // Render all entities which should be rendered
        for( auto it = entities.begin(); it != entities.end(); ++it )
        {
            for( auto rSIt = renderingSystems.begin(); rSIt != renderingSystems.end(); ++rSIt )
            {
                // Check if entity should be processed by the rendering system. If so, do it
                if( *it != nullptr && (*rSIt)->shouldRenderEntity( **it ) )
                {
                    (*rSIt)->render( **it );
                }
            }
        }
    }
}
