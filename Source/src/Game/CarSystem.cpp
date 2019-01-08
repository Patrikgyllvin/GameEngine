//
//  CarSystem.cpp
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-07.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#include "../../include/Game/CarSystem.h"

CarSystem::CarSystem( Engine::EventManager& evtMgr )
:
Engine::IEventListener( evtMgr ),
registered( false ),
maxLateralImpulse( 3 ),
time( 0.0 )
{
    eventManager.subscribeToEvent( this, Engine::EVENT_ENTITY_COMPONENT_ADDED );
}

CarSystem::~CarSystem()
{}

bool CarSystem::shouldProcessEntity( const Engine::Entity& entity )
{
    return ( entity.hasComponent( COMPONENT_CAR_BIT | COMPONENT_PHYSICS_BIT | COMPONENT_RAYCAST_BIT | COMPONENT_DNA_BIT | COMPONENT_NEURAL_NETWORK_BIT ) ||
            entity.hasComponent( COMPONENT_CAR_BIT | COMPONENT_PHYSICS_BIT ) );
}

void CarSystem::BeginContact( b2Contact* contact )
{
    if( contact->GetFixtureB()->GetFilterData().categoryBits == 0x0001 && contact->GetFixtureA()->GetFilterData().categoryBits == 0x0002 && !contact->GetFixtureB()->IsSensor() )
    {
        if( contact->GetFixtureB()->GetBody()->GetUserData() )
            static_cast< PhysicsBodyComponent* >( contact->GetFixtureB()->GetBody()->GetUserData() )->setAlive( false );
    }
    else if( contact->GetFixtureA()->GetFilterData().categoryBits == 0x0001 && contact->GetFixtureB()->GetFilterData().categoryBits == 0x0002 && !contact->GetFixtureA()->IsSensor() )
    {
        if( contact->GetFixtureB()->GetBody()->GetUserData() )
            static_cast< PhysicsBodyComponent* >( contact->GetFixtureB()->GetBody()->GetUserData() )->setAlive( false );
    }
}

void CarSystem::EndContact( b2Contact* contact )
{}

void CarSystem::init( Engine::EntityManager& entityManager )
{}

void CarSystem::preProcess()
{
    time += 1 / 100.0;
}

void CarSystem::processEvent( const Engine::IEvent &e )
{
    const Engine::EntityEvent& eEvent = static_cast< const Engine::EntityEvent& >( e );
    Engine::Entity& entity = *eEvent.entity;

    ComponentType typeAdded = static_cast< Engine::Component* >( eEvent.data )->getType();
    if( shouldProcessEntity( entity ) && ( typeAdded == COMPONENT_PHYSICS ||
                                            typeAdded == COMPONENT_CAR ||
                                            typeAdded == COMPONENT_RAYCAST ||
                                            typeAdded == COMPONENT_DNA ||
                                            typeAdded == COMPONENT_NEURAL_NETWORK ) )
    {
        PhysicsBodyComponent& physComp = static_cast< PhysicsBodyComponent& >( entity.getFirstComponentOf( COMPONENT_PHYSICS ) );
        CarComponent& carComp = static_cast< CarComponent& >( entity.getFirstComponentOf( COMPONENT_CAR ) );

        if( !physComp.getBody() )
            return;

        std::vector< Engine::Entity* >& tires = carComp.getTires();
        if( tires.size() != 4 )
        {
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;

            b2FixtureDef fixDef;
            fixDef.filter.maskBits = 0x0002;
            fixDef.filter.categoryBits = 0x0001;
            fixDef.friction = 0.3;

            b2RevoluteJointDef jointDef;
            jointDef.bodyA = physComp.getBody();
            jointDef.enableLimit = true;
            jointDef.lowerAngle = glm::radians( -40.0 );
            jointDef.upperAngle = glm::radians( 40.0 );
            jointDef.localAnchorB.SetZero();

            b2PolygonShape* tireShape = new b2PolygonShape;
            tireShape->SetAsBox( 0.25, 0.5 );

            Engine::Entity* tire = &entity.entityManager.genEntity().addComponent( new TireComponent() ).addComponent( new PhysicsBodyComponent( bodyDef, fixDef, tireShape, 0.25, 0.5, 1 ) );

            jointDef.bodyB = static_cast< PhysicsBodyComponent& >( tire->getFirstComponentOf( COMPONENT_PHYSICS ) ).getBody();
            jointDef.localAnchorA.Set( -1, 1.25 );
            *carComp.getFLJoint() = ( b2RevoluteJoint* )physComp.getBody()->GetWorld()->CreateJoint( &jointDef );

            tires.push_back( tire );

            tireShape = new b2PolygonShape;
            tireShape->SetAsBox( 0.25, 0.5 );

            tire = &entity.entityManager.genEntity().addComponent( new TireComponent() ).addComponent( new PhysicsBodyComponent( bodyDef, fixDef, tireShape, 0.25, 0.5, 1 ) );

            jointDef.bodyB = static_cast< PhysicsBodyComponent& >( tire->getFirstComponentOf( COMPONENT_PHYSICS ) ).getBody();
            jointDef.localAnchorA.Set( 1, 1.25 );
            *carComp.getFRJoint() = ( b2RevoluteJoint* )physComp.getBody()->GetWorld()->CreateJoint( &jointDef );

            tires.push_back( tire );

            b2RevoluteJointDef rearJointDef;
            rearJointDef.bodyA = physComp.getBody();
            rearJointDef.enableLimit = true;
            rearJointDef.lowerAngle = 0;
            rearJointDef.upperAngle = 0;
            rearJointDef.localAnchorB.SetZero();

            tireShape = new b2PolygonShape;
            tireShape->SetAsBox( 0.25, 0.5 );

            tire = &entity.entityManager.genEntity().addComponent( new TireComponent() ).addComponent( new PhysicsBodyComponent( bodyDef, fixDef, tireShape, 0.25, 0.5, 1 ) );

            rearJointDef.bodyB = static_cast< PhysicsBodyComponent& >( tire->getFirstComponentOf( COMPONENT_PHYSICS ) ).getBody();
            rearJointDef.localAnchorA.Set( -1, -1.25 );
            physComp.getBody()->GetWorld()->CreateJoint( &rearJointDef );

            tires.push_back( tire );

            tireShape = new b2PolygonShape;
            tireShape->SetAsBox( 0.25, 0.5 );

            tire = &entity.entityManager.genEntity().addComponent( new TireComponent() ).addComponent( new PhysicsBodyComponent( bodyDef, fixDef, tireShape, 0.25, 0.5, 1 ) );

            rearJointDef.bodyB = static_cast< PhysicsBodyComponent& >( tire->getFirstComponentOf( COMPONENT_PHYSICS ) ).getBody();
            rearJointDef.localAnchorA.Set( 1, -1.25 );
            physComp.getBody()->GetWorld()->CreateJoint( &rearJointDef );

            tires.push_back( tire );
        }
    }
}

void CarSystem::processEntity( Engine::Entity& entity )
{
    CarComponent& carComp = static_cast< CarComponent& >( entity.getFirstComponentOf( COMPONENT_CAR ) );
    PhysicsBodyComponent& physComp = static_cast< PhysicsBodyComponent& >( entity.getFirstComponentOf( COMPONENT_PHYSICS ) );

    if( !registered )
    {
        physComp.getBody()->GetWorld()->SetContactListener( this );
        registered = true;
    }
    
    // Speed
    b2Vec2 currentForwardNormal = physComp.getBody()->GetWorldVector( b2Vec2( 0, 1 ) );
    float currentSpeed = b2Dot( getForwardVelocity( physComp.getBody() ), currentForwardNormal );
    
    Eigen::Vector2f output;
    
        std::vector< Engine::Component* >& rays = entity.getComponents( COMPONENT_RAYCAST );

        // Ray 1
        RayCastComponent* rayComp = static_cast< RayCastComponent* >( rays[ 0 ] );

        b2Vec2 directionVec = b2Vec2( cosf( physComp.getBody()->GetAngle() + M_PI_2 ), sinf( physComp.getBody()->GetAngle() + M_PI_2 ) );
        directionVec.Normalize();

        rayComp->setP1( physComp.getBody()->GetPosition() + 2 * directionVec );
        rayComp->setP2( physComp.getBody()->GetPosition() + 12 * directionVec );

        // Ray 2
        rayComp = static_cast< RayCastComponent* >( rays[ 1 ] );
    /*
        directionVec = b2Vec2( cosf( physComp.getBody()->GetAngle() + M_PI_2 ), sinf( physComp.getBody()->GetAngle() + M_PI_2 ) );
        directionVec.Normalize();
    */
        b2Vec2 directionVec2 = b2Vec2( cosf( physComp.getBody()->GetAngle() + M_PI_2 + M_PI_4 ), sinf( physComp.getBody()->GetAngle() + M_PI_2 + M_PI_4 ) );
        directionVec2.Normalize();

        rayComp->setP1( physComp.getBody()->GetPosition() + 2 * directionVec );
        rayComp->setP2( physComp.getBody()->GetPosition() + 2 * directionVec + 12 * directionVec2 );

        // Ray 3
        rayComp = static_cast< RayCastComponent* >( rays[ 2 ] );

        directionVec = b2Vec2( cosf( physComp.getBody()->GetAngle() + M_PI_2 ), sinf( physComp.getBody()->GetAngle() + M_PI_2 ) );
        directionVec.Normalize();

        directionVec2 = b2Vec2( cosf( physComp.getBody()->GetAngle() + M_PI_2 - M_PI_4 ), sinf( physComp.getBody()->GetAngle() + M_PI_2 - M_PI_4 ) );
        directionVec2.Normalize();

        rayComp->setP1( physComp.getBody()->GetPosition() + 2 * directionVec );
        rayComp->setP2( physComp.getBody()->GetPosition() + 2 * directionVec + 12 * directionVec2 );

    if( carComp.isAutonomous() )
    {
        // Neural network control
        NeuralNetworkComponent& nnComp = static_cast< NeuralNetworkComponent& >( entity.getFirstComponentOf( COMPONENT_NEURAL_NETWORK ) );
        Eigen::Vector4f input;
        // Sensors
        input( 2 ) = rayComp->getOutput().fraction;

        for( int i = 0; i != 2; ++i )
        {
            rayComp = static_cast< RayCastComponent* >( rays[ i ] );
            input( i ) = rayComp->getOutput().fraction;
        }

        // Speed
        input( 3 ) = abs( currentSpeed ) / carComp.getMaxSpeedFwd();

        output = nnComp.feedForward( input );
    }
    
    std::vector< Engine::Entity* >& tires = carComp.getTires();
    for( auto it = tires.begin(); it != tires.end(); ++it )
    {
        PhysicsBodyComponent& tirePhys = static_cast< PhysicsBodyComponent& >( (*it)->getFirstComponentOf( COMPONENT_PHYSICS ) );

        updateFriction( tirePhys.getBody() );

        // Is car "Dead"?, Don't update drive
        if( !physComp.isAlive() || !tirePhys.isAlive() )
        {
            physComp.setAlive( false );
            physComp.getBody()->SetActive( false );
            continue;
        }
        
        if( carComp.isAutonomous() )
            updateDrive( tirePhys.getBody(), carComp, output( 0 ), output( 1 ) );
        else
            updateDrive( tirePhys.getBody(), carComp, 0, 0 );
    }

    float currentDistance = currentSpeed * ( 1 / 100.0 );
    if( physComp.isAlive() )
        carComp.addDistance( currentDistance );

    if( ( abs( currentDistance ) < 0.05 ) && ( time - carComp.getTimeOut() ) > 2.0 && carComp.getTimeOut() != -1.0 && carComp.isAutonomous() )
    {
        physComp.setAlive( false );
    }
    else if( abs( currentDistance ) >= 0.05 )
    {
        carComp.setTimeOut( time );
    }
}

void CarSystem::postProcess()
{}

b2Vec2 CarSystem::getLateralVelocity( b2Body* body )
{
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2( 1, 0 ) );

    return b2Dot( currentRightNormal, body->GetLinearVelocity() ) * currentRightNormal;
}

b2Vec2 CarSystem::getForwardVelocity( b2Body* body )
{
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2( 0, 1 ) );

    return b2Dot( currentRightNormal, body->GetLinearVelocity() ) * currentRightNormal;
}

void CarSystem::updateFriction( b2Body* body )
{
    b2Vec2 impulse = body->GetMass() * -getLateralVelocity( body );
    if ( impulse.Length() > maxLateralImpulse )
        impulse *= maxLateralImpulse / impulse.Length();

    body->ApplyLinearImpulse( impulse, body->GetWorldCenter(), true );

    body->ApplyAngularImpulse( 0.1f * body->GetInertia() * -body->GetAngularVelocity(), true );

    b2Vec2 currentForwardNormal = getForwardVelocity( body );

    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -2 * currentForwardSpeed;

    body->ApplyForce( dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true );
}

void CarSystem::updateDrive( b2Body* body, CarComponent& carComp, float angle, float force )
{
    bool autonomous = carComp.isAutonomous();
    float desiredSpeed = 0;
    
    if( Engine::InputHandler::getButton( "Forward" ) && !autonomous )
    {
        desiredSpeed = carComp.getMaxSpeedFwd();
    }
    else if( Engine::InputHandler::getButton( "Backward" ) && !autonomous )
    {
        desiredSpeed = carComp.getMaxSpeedBwd();
    }

    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2( 0, 1 ) );
    float currentSpeed = b2Dot( getForwardVelocity( body ), currentForwardNormal );
    
    if( !autonomous )
    {
        if( !desiredSpeed )
            force = 0;
        else if ( desiredSpeed > currentSpeed )
            force = carComp.getMaxEngineForceFwd();
        else if ( desiredSpeed < currentSpeed )
            force = -carComp.getMaxEngineForceBwd();
        else
            force = 0;
    }
    else
    {
        if( force < 0 && currentSpeed > carComp.getMaxSpeedBwd() )
            force = force * carComp.getMaxEngineForceBwd();
        else if( force > 0 && currentSpeed < carComp.getMaxSpeedFwd() )
            force = force* carComp.getMaxEngineForceFwd();
    }
    
    if( force )
        body->ApplyForce( force * currentForwardNormal, body->GetWorldCenter(), true );

    float lockAngle = glm::radians( 40.0 );
    float turnSpeedPerSec = glm::radians( 320.0 );
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;

    
    if( Engine::InputHandler::getButton( "Turn left" ) && !autonomous )
    {
        angle = 1.0;
    }
    else if( Engine::InputHandler::getButton( "Turn right" ) && !autonomous )
    {
        angle = -1.0;
    }
    
    angle *= lockAngle;

    float angleNow = ( *carComp.getFLJoint() )->GetJointAngle();
    float angleNowGlobal = ( *carComp.getFLJoint() )->GetBodyB()->GetAngle();
    float angleToTurn = angle - angleNow;
    angleToTurn = b2Clamp( angleToTurn, -turnPerTimeStep, turnPerTimeStep );
    float newAngle = angleNowGlobal + angleToTurn;

    b2Vec2 posLeft = ( *carComp.getFLJoint() )->GetBodyB()->GetPosition();
    ( *carComp.getFLJoint() )->GetBodyB()->SetTransform( posLeft, newAngle );

    b2Vec2 posRight = ( *carComp.getFRJoint() )->GetBodyB()->GetPosition();
    ( *carComp.getFRJoint() )->GetBodyB()->SetTransform( posRight, newAngle );
}
