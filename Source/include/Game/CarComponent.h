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

#include "TireComponent.h"

#include <Box2D/Box2D.h>
#include <vector>

class CarComponent : public Engine::Component
{
public:
    CarComponent()
    :
    Engine::Component( COMPONENT_CAR ),
    maxSpeedFwd( 60 ),
    maxSpeedBwd( 5.5 ),
    maxEngineForce( 150 )
    {
        tires.reserve( 4 );
    }
    
    ~CarComponent()
    {}
    
    std::vector< Engine::Entity* >& getTires()
    {
        return this->tires;
    }
    
private:
    // Tire-entitiy ref vector. Each Tire has PhysicsComponent, TireComponent
    std::vector< Engine::Entity* > tires;
    
    float maxSpeedFwd, maxSpeedBwd, maxEngineForce;
};

#endif /* CarComponent_h */
