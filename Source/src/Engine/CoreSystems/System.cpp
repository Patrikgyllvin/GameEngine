#include "Engine/CoreSystems/System.h"

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
