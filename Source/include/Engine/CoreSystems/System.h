#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>

#include "../Events/EventManager.h"
#include "Entity.h"

namespace Engine
{
	class System
	{
	public:
		System();
		virtual ~System();

		virtual bool shouldProcessEntity( const Entity& entity ) = 0;

		void update( Entity& entity );

	protected:
		virtual void init() = 0;

		virtual void preProcess() = 0;

		virtual void processEntity( Entity& entity ) = 0;

		virtual void postProcess() = 0;
	};
}

#endif
