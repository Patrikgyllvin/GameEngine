#ifndef ENTITYEVENT_H
#define ENTITYEVENT_H

#include "Events.h"

#include "../Entity Core/Entity.h"

namespace Engine
{
	struct EntityEvent : public IEvent
	{
		EntityEvent( EventType eType, Entity* e ) : IEvent( eType ), entity( e ) {}

		Entity* entity;
	};
}

#endif
