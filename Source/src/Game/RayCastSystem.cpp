//
//  RayCastSystem.cpp
//  GameEngine
//
//  Created by Patrik Gyllvin on 2018-01-29.
//  Copyright © 2018 Patrik Gyllvin. All rights reserved.
//

#include "../../include/Game/RayCastSystem.h"

RayCastSystem::RayCastSystem( Engine::EventManager& evtMgr )
:
Engine::IEventListener( evtMgr )
{
    eventManager.subscribeToEvent( this, Engine::EVENT_ENTITY_COMPONENT_ADDED );
}

RayCastSystem::~RayCastSystem()
{}

bool RayCastSystem::shouldProcessEntity( const Engine::Entity& entity )
{
    return entity.hasComponent( COMPONENT_PHYSICS_BIT | COMPONENT_RAYCAST_BIT );
}

void RayCastSystem::processEvent( const Engine::IEvent& e )
{
    const Engine::EntityEvent& eEvent = static_cast< const Engine::EntityEvent& >( e );
    Engine::Entity& entity = *eEvent.entity;

    if( shouldProcessEntity( entity ) && static_cast< Engine::Component* >( eEvent.data )->getType() == COMPONENT_RAYCAST )
    {
        PhysicsBodyComponent& physComp = static_cast< PhysicsBodyComponent& >( entity.getFirstComponentOf( COMPONENT_PHYSICS ) );
        RayCastComponent& rayComp = *static_cast< RayCastComponent* >( eEvent.data );

        b2PolygonShape ray;
        float length = b2Vec2( rayComp.getInput().p2 - rayComp.getInput().p1 ).Length();
        ray.SetAsBox( 0.05, length, rayComp.getInput().p1, 0.0 );

        b2FixtureDef fixDef;
        fixDef.density = 0.0;
        fixDef.shape = &ray;
        fixDef.isSensor = true;
        fixDef.userData = new b2Vec3( 0.05, length, 0.0 );

        rayComp.setFixture( physComp.getBody()->CreateFixture( &fixDef ) );
    }
}

void RayCastSystem::init( Engine::EntityManager& entityManager )
{}

void RayCastSystem::preProcess()
{}

void RayCastSystem::processEntity( Engine::Entity& entity )
{
    std::vector< Engine::Component* > rays = entity.getComponents( COMPONENT_RAYCAST );
    PhysicsBodyComponent& physComp = static_cast< PhysicsBodyComponent& >( entity.getFirstComponentOf( COMPONENT_PHYSICS ) );

    for( auto it = rays.begin(); it != rays.end(); ++it )
    {
        RayCastComponent* rayComp = static_cast< RayCastComponent* >( *it );

        b2Vec2 rayVec = b2Vec2( rayComp->getInput().p2 - rayComp->getInput().p1 );
        float length = rayVec.Normalize();

        b2Vec2 forward = physComp.getBody()->GetWorldVector( b2Vec2( 0, 1 ) );
        forward.Normalize();

        float angle = atan2( rayVec.y, rayVec.x ) - atan2( forward.y, forward.x );

        static_cast< b2PolygonShape* >( rayComp->getFixture().GetShape() )->SetAsBox( 0.05, length / 2, ( 0.5 * rayComp->getInput().p1 - 0.5 * physComp.getBody()->GetPosition() ) + ( length / 4 ) * rayVec, angle );

        delete static_cast< b2Vec2* >( rayComp->getFixture().GetUserData() );
        rayComp->getFixture().SetUserData( new b2Vec3( 0.05, length / 2, angle ) );

        float closest = 1.0;
        b2Vec2 normal( 0, 0 );

        for( b2Body* b = physComp.getBody()->GetWorld()->GetBodyList(); b; b = b->GetNext() )
        {
            for( b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext() )
            {
                // Don't cast to cars or other rays...
                if( f->IsSensor() || f->GetFilterData().categoryBits == 0x0001 )
                    continue;

                b2RayCastOutput output;
                if( !f->RayCast( &output, rayComp->getInput(), 0 ) )
                    continue;
                if( output.fraction < closest )
                {
                    closest = output.fraction;
                    normal = output.normal;
                }
            }
        }

        /*
        if( physComp.isAlive() )
            std::cout << "RayCast fraction: " << closest << '\n';
        */
        rayComp->getOutput().fraction = closest;
        rayComp->getOutput().normal = normal;
    }
}

void RayCastSystem::postProcess()
{}
