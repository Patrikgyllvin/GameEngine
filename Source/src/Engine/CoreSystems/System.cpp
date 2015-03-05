#ifndef __APPLE__
#include "Engine/CoreSystems/System.h"
#else
#include "System.h"
#endif

namespace Engine
{
	System::System()
	{}

	System::~System()
	{}

	void System::update( const Entity& entity )
	{
		preProcess();

		processEntity( entity );

		postProcess();
	}
}
