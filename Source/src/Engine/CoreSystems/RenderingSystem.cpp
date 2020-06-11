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
    RenderingSystem::RenderingSystem()
    {}

    RenderingSystem::~RenderingSystem()
    {}

	// Override initialize, initialize standard shaders statically and call init...
	void RenderingSystem::initialize( EntityManager &entityManager )
	{
#if !defined __APPLE__ || defined _MAC_MAKEFILE
    shader.loadAndCompile( "Res/Engine/Shaders/std.vs", "Res/Engine/Shaders/std.fs" );
    shaderNoTex.loadAndCompile( "Res/Engine/Shaders/NoTex.vs", "Res/Engine/Shaders/NoTex.fs" );
#else
    shader.loadAndCompile( "std.vs", "std.fs" );
    shaderNoTex.loadAndCompile( "NoTex.vs", "NoTex.fs" );
#endif
	}

    void RenderingSystem::render( Entity& entity )
    {
        preRender();

        renderEntity( entity );

        postRender();
    }
}
