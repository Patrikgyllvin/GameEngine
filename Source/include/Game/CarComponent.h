//
//  CarComponent.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-06.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#ifndef CarComponent_h
#define CarComponent_h

#include "../Engine/CoreComponents/Component.h"
#include "../Engine/EntityCore/Entity.h"

#include "TireComponent.h"

#include <Box2D/Box2D.h>
#include <vector>

class CarComponent : public Engine::Component
{
public:
    CarComponent( bool selfDrive )
    :
    Engine::Component( COMPONENT_CAR ),
    maxSpeedFwd( 40.0 ),
    maxSpeedBwd( -10.0 ),
    maxEngineForceFwd( 300.0 ),
    maxEngineForceBwd( 100.0 ),
    distance( 0.0 ),
    timeOut( -1.0 ),
    selfDrive( selfDrive )
    {
        tires.reserve( 4 );
    }

    ~CarComponent()
    {
        for( auto it = tires.begin(); it != tires.end(); ++it )
            (*it)->destroyEntity();
    }

    std::vector< Engine::Entity* >& getTires()
    {
        return this->tires;
    }

    const float& getMaxSpeedFwd() const
    {
        return this->maxSpeedFwd;
    }

    const float& getMaxSpeedBwd() const
    {
        return this->maxSpeedBwd;
    }

    const float& getMaxEngineForceFwd() const
    {
        return this->maxEngineForceFwd;
    }

    const float& getMaxEngineForceBwd() const
    {
        return this->maxEngineForceBwd;
    }

    b2RevoluteJoint** getFLJoint()
    {
        return &this->flJoint;
    }

    b2RevoluteJoint** getFRJoint()
    {
        return &this->frJoint;
    }

    void setDistance( const float& distance )
    {
        this->distance = distance;
    }

    void addDistance( const float& distance )
    {
        this->distance += distance;
    }

    const float& getDistance() const
    {
        return this->distance;
    }

    void setTimeOut( float timeOut )
    {
        this->timeOut = timeOut;
    }

    const float& getTimeOut() const
    {
        return this->timeOut;
    }

    const bool& isAutonomous() const
    {
        return this->selfDrive;
    }

private:
    // Tire-entitiy ref vector. Each Tire has PhysicsComponent, TireComponent
    std::vector< Engine::Entity* > tires;

    float maxSpeedFwd, maxSpeedBwd, maxEngineForceFwd, maxEngineForceBwd;

    b2RevoluteJoint* flJoint, *frJoint;

    float distance, timeOut;

    bool selfDrive;
};

#endif /* CarComponent_h */
