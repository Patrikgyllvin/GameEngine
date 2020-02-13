//
//  RenderingSystem.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-13.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#ifndef RenderingSystem_h
#define RenderingSystem_h

#include "System.h"

namespace Engine {
    class RenderingSystem : public System
    {
    public:
        RenderingSystem();
        virtual ~RenderingSystem();

        virtual bool shouldRenderEntity( const Entity& entity ) = 0;

        void render( Entity& entity );

    protected:
        virtual void preRender() = 0;

        virtual void renderEntity( Entity& entity ) = 0;

        virtual void postRender() = 0;
    };
}

#endif /* RenderingSystem_h */
