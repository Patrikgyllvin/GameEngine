#if !defined(__APPLE__) || defined(_MAC_MAKEFILE)
#include "../../../include/Engine/CoreSystems/System.h"
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
