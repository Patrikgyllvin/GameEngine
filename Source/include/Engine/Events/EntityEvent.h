#ifndef ENTITYEVENT_H
#define ENTITYEVENT_H

#include "Events.h"

namespace Engine
{
    class Entity;
    
	struct EntityEvent : public IEvent
	{
		EntityEvent( EventType eType, Entity* e, void* data ) : IEvent( eType ), entity( e ), data( data ) {}

		Entity* entity;
        
        void* data;
	};
}

#endif
