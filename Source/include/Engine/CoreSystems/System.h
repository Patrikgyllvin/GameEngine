#ifndef SYSTEM_H
#define SYSTEM_H

#include "../Events/EventManager.h"
#include "../EntityCore/Entity.h"

#include "../../ComponentTypes.h"

namespace Engine
{
	class System
	{
	public:
		System();
		virtual ~System();

		virtual bool shouldProcessEntity( const Entity& entity ) = 0;

   		void initialize( EntityManager& entityManager );
        void update();
		void updateEntity( Entity& entity );

	protected:
		virtual void init( EntityManager& entityManager ) = 0;

		virtual void preProcess() = 0;

		virtual void processEntity( Entity& entity ) = 0;

		virtual void postProcess() = 0;
	};
}

#endif
