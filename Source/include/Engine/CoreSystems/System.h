#ifndef SYSTEM_H
#define SYSTEM_H

#include "../Events/EventManager.h"
#include "Entity.h"

#include "../../ComponentTypes.h"

namespace Engine
{
	class System
	{
	public:
		System();
		virtual ~System();

		virtual bool shouldProcessEntity( const Entity& entity ) = 0;

        void initialize();
        void update();
		void updateEntity( Entity& entity );

	protected:
		virtual void init() = 0;

		virtual void preProcess() = 0;

		virtual void processEntity( Entity& entity ) = 0;

		virtual void postProcess() = 0;
	};
}

#endif
