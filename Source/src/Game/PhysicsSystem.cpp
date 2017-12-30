//
//  PhysicsSystem.cpp
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-07.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
:
gravity( 0.0, -9.81 )
{
    world = new b2World( gravity );
}

PhysicsSystem::PhysicsSystem( b2Vec2 gravity )
:
gravity( gravity ),
world( new b2World( gravity ) )
{}

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

void PhysicsSystem::init()
{}

void PhysicsSystem::preProcess()
{
    // Do physx
    world->Step( 1.0/60.0, 10, 10 );
}

void PhysicsSystem::processEntity( Engine::Entity &entity )
{
    PhysicsBodyComponent& physComp = static_cast< PhysicsBodyComponent& >( entity.getFirstComponentOf( COMPONENT_PHYSICS ) );
    
    if( physComp.getBody() == nullptr )
    {
        b2Body* body;
        body = world->CreateBody( &physComp.getBodyDefinition() );
        
        body->CreateFixture( &physComp.getFixtureDefinition() );
        
        physComp.setBody( body );
    }
}

void PhysicsSystem::postProcess()
{}
