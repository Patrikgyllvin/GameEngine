//
//  CarSystem.cpp
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-07.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#include "CarSystem.h"

CarSystem::CarSystem()
{}

CarSystem::~CarSystem()
{}

bool CarSystem::shouldProcessEntity( const Engine::Entity& entity )
{
    return entity.hasComponent( COMPONENT_CAR_BIT | COMPONENT_PHYSICS_BIT );
}

void CarSystem::init()
{}

void CarSystem::preProcess()
{}

void CarSystem::processEntity( Engine::Entity& entity )
{
    CarComponent& carComp = static_cast< CarComponent& >( entity.getFirstComponentOf( COMPONENT_CAR ) );
    
    std::vector< Engine::Entity* >& tires = carComp.getTires();
    if( tires.size() != 4 )
    {
        for( int i = 0; i != 4; ++i )
            tires.push_back( &entity.entityManager.genEntity().addComponent( new TireComponent() ) );
    }
    
    PhysicsBodyComponent& physComp = static_cast< PhysicsBodyComponent& >( entity.getFirstComponentOf( COMPONENT_PHYSICS ) );
    if( physComp.getBody()->GetPosition().y < -5 )
    {
        for( auto it = carComp.getTires().begin(); it != carComp.getTires().end(); ++it )
            (*it)->destroyEntity();
        entity.destroyEntity();
    }
}

void CarSystem::postProcess()
{}
