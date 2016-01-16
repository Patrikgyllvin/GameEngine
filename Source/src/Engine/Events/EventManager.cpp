#if !defined(__APPLE__) || defined(_MAC_MAKEFILE)
#include "../../../include/Engine/Events/EventManager.h"
#else
#include "EventManager.h"
#endif

namespace Engine
{
	EventManager::EventManager()
	:
	globalListeners()
	{
		listeners.resize( EVENT_LAST );
	}

	EventManager::~EventManager()
	{}

	void EventManager::subscribeToEvent( IEventListener* listener, EventType eType )
	{
		std::vector< IEventListener* >& listenerListType = listeners[ eType ];
		listenerListType.push_back( listener );
	}

	void EventManager::unsubsribeFromEvent( IEventListener* listener, EventType eType )
	{
		std::vector< IEventListener* >& listenerListType = listeners[ eType ];

		for( std::vector< IEventListener* >::const_iterator it = listenerListType.begin(); it != listenerListType.end(); ++it )
		{
			if( (*it) == listener )
			{
				listenerListType.erase( it );
				return;
			}
		}
	}

	void EventManager::subscribeGlobally( IEventListener* listener )
	{
		globalListeners.push_back( listener );
	}

	void EventManager::unsubscribeGlobally( IEventListener* listener )
	{
		for( std::vector< IEventListener* >::const_iterator it = globalListeners.begin(); it != globalListeners.end(); ++it )
		{
			if( (*it) == listener )
			{
				globalListeners.erase( it );
				return;
			}
		}
	}

	void EventManager::unsubscribeAll()
	{
		globalListeners.clear();

		for( unsigned int i = 0; i < EVENT_LAST; i++ )
		{
			listeners[ i ].clear();
		}

		listeners.clear();
	}

	void EventManager::pushEvent( const IEvent& e )
	{
		for( std::vector< IEventListener* >::const_iterator it = globalListeners.begin(); it != globalListeners.end(); ++it )
		{
			( *it )->processEvent( e );
		}

		std::vector< IEventListener* >& listenerListType = listeners[ e.getType() ];

		for( std::vector< IEventListener* >::const_iterator it = listenerListType.begin(); it != listenerListType.end(); ++it )
		{
			( *it )->processEvent( e );
		}
	}
}
