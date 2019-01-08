#include "../../../include/Engine/CoreSystems/System.h"

namespace Engine
{
	System::System()
	{}

	System::~System()
	{}

    void System::initialize( EntityManager& entityManager )
    {
        init( entityManager );
    }

	void System::update()
	{
		preProcess();
	}

    void System::updateEntity( Engine::Entity &entity )
    {
        processEntity( entity );
    }
}
