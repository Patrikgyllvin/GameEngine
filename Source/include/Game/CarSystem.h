//
//  CarSystem.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-07.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#ifndef CarSystem_h
#define CarSystem_h

#include <glm/glm.hpp>
#include <Eigen/Eigen>

#include "../Engine/CoreSystems/System.h"

#include "PhysicsBodyComponent.h"
#include "RayCastComponent.h"

#include "NeuralNetworkComponent.h"

#include "CarComponent.h"

#include "../Engine/Input/InputHandler.h"

class CarSystem : public Engine::System, public b2ContactListener, public Engine::IEventListener
{
public:
    CarSystem( Engine::EventManager& evtMgr );
    ~CarSystem();

    virtual bool shouldProcessEntity( const Engine::Entity& entity );

    virtual void BeginContact( b2Contact* contact );
    virtual void EndContact( b2Contact* contact );

    virtual void processEvent( const Engine::IEvent& e );

protected:
    virtual void init( Engine::EntityManager& entityManager );

    virtual void preProcess();
    virtual void processEntity( Engine::Entity& entity );
    virtual void postProcess();

private:
    bool registered;

    float maxLateralImpulse, time;

    b2Vec2 getLateralVelocity( b2Body* body );
    b2Vec2 getForwardVelocity( b2Body* body );

    void updateFriction( b2Body* body );
    void updateDrive( b2Body* body, CarComponent& carComp, float angle = 0, float force = 0 );
};

#endif /* CarSystem_h */
