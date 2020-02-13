//
//  PhysicsSystem.cpp
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-07.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#include "../../include/Game/PhysicsSystem.h"

PhysicsSystem::PhysicsSystem( Engine::EventManager& evtMgr )
:
gravity( 0.0, -9.81 ),
Engine::IEventListener( evtMgr )
{
    world = new b2World( gravity );

    eventManager.subscribeToEvent( this, Engine::EVENT_ENTITY_COMPONENT_ADDED );
}

PhysicsSystem::PhysicsSystem( b2Vec2 gravity, Engine::EventManager& evtMgr )
:
gravity( gravity ),
Engine::IEventListener( evtMgr ),
world( new b2World( gravity ) )
{
    eventManager.subscribeToEvent( this, Engine::EVENT_ENTITY_COMPONENT_ADDED );
}

PhysicsSystem::~PhysicsSystem()
{
    for ( b2Body* body = world->GetBodyList(); body; body = body->GetNext() )
    {
        world->DestroyBody( body );
    }

    delete world;
}

bool PhysicsSystem::shouldProcessEntity( const Engine::Entity &entity )
{
    return entity.hasComponent( COMPONENT_PHYSICS_BIT );
}

void PhysicsSystem::processEvent( const Engine::IEvent &e )
{
    const Engine::EntityEvent& eEvent = static_cast< const Engine::EntityEvent& >( e );
    Engine::Entity& entity = *eEvent.entity;

    if( shouldProcessEntity( entity ) && static_cast< Engine::Component* >( eEvent.data )->getType() == COMPONENT_PHYSICS )
    {
        PhysicsBodyComponent& physComp = *static_cast< PhysicsBodyComponent* >( eEvent.data );

        if( physComp.getBody() == nullptr )
        {
            b2Body* body;
            body = world->CreateBody( &physComp.getBodyDefinition() );

            body->CreateFixture( &physComp.getFixtureDefinition() );

            physComp.setBody( body );
        }
    }
}

void PhysicsSystem::init( Engine::EntityManager& entityManager )
{}

void PhysicsSystem::preProcess()
{
    // Do physx
    world->Step( 1.0/100.0, 8, 3 );
}

void PhysicsSystem::processEntity( Engine::Entity &entity )
{}

void PhysicsSystem::postProcess()
{}
