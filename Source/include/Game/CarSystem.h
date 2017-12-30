//
//  CarSystem.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-07.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#ifndef CarSystem_h
#define CarSystem_h

#include "../Engine/CoreSystems/System.h"

#include "PhysicsBodyComponent.h"

#include "CarComponent.h"

#include "../Engine/Input/InputHandler.h"

class CarSystem : public Engine::System
{
public:
    CarSystem();
    ~CarSystem();
    
    virtual bool shouldProcessEntity( const Engine::Entity& entity );
    
protected:
    virtual void init();
    
    virtual void preProcess();
    virtual void processEntity( Engine::Entity& entity );
    virtual void postProcess();
};

#endif /* CarSystem_h */
