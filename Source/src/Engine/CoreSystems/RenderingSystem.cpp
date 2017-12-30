//
//  RenderingSystem.cpp
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-13.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#include <RenderingSystem.h>

namespace Engine
{
    RenderingSystem::RenderingSystem()
    {}
    
    RenderingSystem::~RenderingSystem()
    {}
    
    void RenderingSystem::render( Entity& entity )
    {
        preRender();
        
        renderEntity( entity );
        
        postRender();
    }
}
