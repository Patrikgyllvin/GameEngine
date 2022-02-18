#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "System.h"

#include "Engine/CoreComponents/MovementComponent.h"
#include "Engine/CoreComponents/TransformComponent.h"

namespace Engine
{
	class MovementSystem : public System
	{
	public:
		MovementSystem();
		virtual ~MovementSystem();

        virtual bool shouldProcessEntity( const Entity& entity );

	protected:
		virtual void init( EntityManager& entityManager );

		virtual void preProcess();
		virtual void processEntity( Entity& entity );
		virtual void postProcess();
	};
}

#endif
