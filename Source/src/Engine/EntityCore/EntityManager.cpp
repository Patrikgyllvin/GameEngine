#include "../../../include/Engine/EntityCore/EntityManager.h"

#include "../../../include/Engine/EntityCore/Entity.h"
#include "../../../include/Engine/CoreSystems/System.h"
#include "../../../include/Engine/CoreSystems/RenderingSystem.h"

#include <ctime>

namespace Engine
{
	EntityManager::EntityManager( EventManager* eManager )
	:
	eventManager( eManager ),
	nextID( 0 ),
	usedIDs(),
	entities()
	{
        entities.reserve( 1000 );
    }

	EntityManager::~EntityManager()
	{
		for( std::vector< Entity* >::iterator it = entities.begin(); it != entities.end(); ++it )
			destroyEntity( *it );

        for( auto it = systems.begin(); it != systems.end(); ++it )
            delete *it;

        for( auto& rSystem : renderingSystems )
            delete rSystem;

		entities.clear();
	}

	Entity& EntityManager::genEntity()
	{
		EntityID id;

		if( !usedIDs.empty() )
		{
			id = usedIDs.front();
			usedIDs.pop();

			Entity* entity = new Entity( id, *this, *eventManager );
			entities[ id ] = entity;

			// Notify systems
			eventManager->pushEvent( EntityEvent( EVENT_ENTITY_CREATED, entity, nullptr ) );

			return *entity;
		}
		else
		{
			id = nextID++;
		}

        Entity* entity = new Entity( id, *this, *eventManager );

		if( id >= entities.capacity() )
        {
			// Add to queue, add entity later when there is time to reserve.
            toBeAdded.push( entity );
        }
        else
        {
            entities.push_back( entity );
        }

		// Notify systems
		eventManager->pushEvent( EntityEvent( EVENT_ENTITY_CREATED, entity, nullptr ) );

		return *entity;
	}

	void EntityManager::destroyEntity( Entity* entity )
    {
		if( !entity )
			return;

		toBeRemoved.push( entity );
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
            (*sIt)->initialize( *this );
        }

        for( auto rSIt = renderingSystems.begin(); rSIt != renderingSystems.end(); ++rSIt )
        {
            (*rSIt)->initialize( *this );
        }
    }

    void EntityManager::update()
    {
		// Remove entities in queue
		while( !toBeRemoved.empty() )
		{
			Entity* e = toBeRemoved.front();
	        e->destroyAllComponents();

	        entities[ e->getID() ] = nullptr;

			usedIDs.push( e->getID() );

			// Notify systems
			eventManager->pushEvent( EntityEvent( EVENT_ENTITY_DESTROYED, e, nullptr ) );

			delete e;
			toBeRemoved.pop();
		}

        // Add entities in queue
        if( !toBeAdded.empty() )
            entities.reserve( toBeAdded.back()->getID() + 100 );

		int added = 0;
        while( !toBeAdded.empty() && added < 100 )
        {
            entities.push_back( toBeAdded.front() );

            toBeAdded.pop();
			++added;
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
