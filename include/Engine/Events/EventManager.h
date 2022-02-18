#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <vector>
#include <map>

#include "Events.h"

namespace Engine
{
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		void subscribeToEvent( IEventListener* listener, EventType eType );
		void unsubsribeFromEvent( IEventListener* listener, EventType eType );

		void subscribeGlobally( IEventListener* listener );
		void unsubscribeGlobally( IEventListener* listener );

		void unsubscribeAll();

		void pushEvent( const IEvent& e ) const;

	private:
		std::vector< IEventListener* > globalListeners;
		std::vector< std::vector< IEventListener* > > listeners;
	};
}

#endif
