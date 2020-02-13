//
//  RayCastSystem.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2018-01-29.
//  Copyright © 2018 Patrik Gyllvin. All rights reserved.
//

#ifndef RayCastSystem_h
#define RayCastSystem_h

#include "../Engine/CoreSystems/System.h"

#include "RayCastComponent.h"
#include "PhysicsBodyComponent.h"

class RayCastSystem : public Engine::System, public Engine::IEventListener
{
public:
    RayCastSystem( Engine::EventManager& evtMgr );
    ~RayCastSystem();

    virtual bool shouldProcessEntity( const Engine::Entity& entity );

    virtual void processEvent( const Engine::IEvent& e );

protected:
    virtual void init( Engine::EntityManager& entityManager );

    virtual void preProcess();
    virtual void processEntity( Engine::Entity& entity );
    virtual void postProcess();

private:

};

#endif /* RayCastSystem_h */
