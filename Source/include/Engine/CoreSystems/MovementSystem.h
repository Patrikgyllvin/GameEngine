#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "System.h"

#include "../CoreComponents/MovementComponent.h"
#include "../CoreComponents/TransformComponent.h"

namespace Engine
{
	class MovementSystem : public System
	{
	public:
		MovementSystem();
		virtual ~MovementSystem();

	protected:
		virtual void init();
		
		virtual void preProcess();
		virtual void processEntity( Entity& entity );
		virtual void postProcess();
	};
}

#endif
