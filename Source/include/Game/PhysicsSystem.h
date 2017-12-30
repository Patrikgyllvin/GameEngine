//
//  PhysicsSystem.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-07.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#ifndef PhysicsSystem_h
#define PhysicsSystem_h

#include <Box2D/Box2D.h>

#include "../Engine/CoreSystems/System.h"

#include "PhysicsBodyComponent.h"

class PhysicsSystem : public Engine::System
{
public:
    PhysicsSystem();
    PhysicsSystem( b2Vec2 gravity );
    ~PhysicsSystem();
    
    virtual bool shouldProcessEntity( const Engine::Entity& entity );
    
protected:
    virtual void init();
    
    virtual void preProcess();
    virtual void processEntity( Engine::Entity& entity );
    virtual void postProcess();
    
private:
    b2World* world;
    b2Vec2 gravity;
};

#endif /* PhysicsSystem_h */
