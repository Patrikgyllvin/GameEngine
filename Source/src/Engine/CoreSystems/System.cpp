#include "System.h"

namespace Engine
{
	System::System( EventManager* evtManager, EntityManager* entManager, unsigned int compTypeBits )
	:
	entityManager( entManager ),
	eventManager( evtManager ),
	typeBits( compTypeBits )
	{
		eventManager->subscribeToEvent( this, EVENT_ENTITY_COMPONENT_ADDED );
		eventManager->subscribeToEvent( this, EVENT_ENTITY_COMPONENT_DESTROYED );
	}

	System::~System()
	{
		eventManager->unsubsribeFromEvent( this, EVENT_ENTITY_COMPONENT_ADDED );
		eventManager->unsubsribeFromEvent( this, EVENT_ENTITY_COMPONENT_DESTROYED );

		chosenOnes.clear();
	}

	void System::processEvent( const IEvent& e )
	{
		switch( e.getType() )
		{
		case EVENT_ENTITY_COMPONENT_ADDED:
		case EVENT_ENTITY_COMPONENT_DESTROYED:
			const EntityEvent& eventData = static_cast< const EntityEvent& >( e );
			Entity* entity = eventData.entity;

			if( ( entity->getTypeBits() & this->typeBits ) == this->typeBits )
				chosenOnes.insert( entity );
			else
				chosenOnes.erase( entity );

			break;
		}
	}

	void System::update()
	{
		preUpdate();

		updateEntities( chosenOnes );

		postUpdate();
	}
}
