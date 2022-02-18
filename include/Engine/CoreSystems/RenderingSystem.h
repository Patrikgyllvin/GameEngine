//
//  RenderingSystem.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-13.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#ifndef RenderingSystem_h
#define RenderingSystem_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "System.h"

#include "Shaders/ShaderManager.h"
#include "Shaders/Shader.h"

namespace Engine {
    class RenderingSystem : public System
    {
    public:
        RenderingSystem();
        virtual ~RenderingSystem();

        virtual bool shouldRenderEntity( const Entity& entity ) = 0;

		void initialize( EntityManager& entityManager );
        void render( Entity& entity );

    protected:
        virtual void preRender() = 0;

        virtual void renderEntity( Entity& entity ) = 0;

        virtual void postRender() = 0;

		static ShaderManager* shaderManager;

		// TODO: Settings struct/object for resolution, FOV, general rendering settings to be used in Render Systems.
    };
}

#endif /* RenderingSystem_h */
