//
//  RenderingSystem.cpp
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-13.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#include "../../../include/Engine/CoreSystems/RenderingSystem.h"

namespace Engine
{
	static ShaderManager shaderManager;

    RenderingSystem::RenderingSystem()
    {}

    RenderingSystem::~RenderingSystem()
    {
		if( shaderManager )
			delete shaderManager;
	}

	// Override initialize, initialize standard shaders statically and call init...
	void RenderingSystem::initialize( EntityManager &entityManager )
	{
		if( !shaderManager )
		{
			shaderManager = new ShaderManager();
		}

		init( entityManager );
	}

    void RenderingSystem::render( Entity& entity )
    {
        preRender();

        renderEntity( entity );

        postRender();
    }
}
