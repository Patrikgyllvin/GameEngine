//
//  RayCastComponent.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2018-01-29.
//  Copyright © 2018 Patrik Gyllvin. All rights reserved.
//

#ifndef RayCastComponent_h
#define RayCastComponent_h

#include "../Engine/CoreComponents/Component.h"

#include <Box2D/Box2D.h>

class RayCastComponent : public Engine::Component
{
public:
    RayCastComponent()
    :
    Component( COMPONENT_RAYCAST )
    {
        input.p1 = b2Vec2( 0, 0 );
        input.p2 = b2Vec2( 0, 0 );
        input.maxFraction = 1.0;
    }

    ~RayCastComponent()
    {}

    void setP1( b2Vec2 p1 )
    {
        this->input.p1 = p1;
    }

    void setP2( b2Vec2 p2 )
    {
        this->input.p2 = p2;
    }

    void setMaxFraction( float32 maxFraction )
    {
        this->input.maxFraction = maxFraction;
    }

    const b2RayCastInput& getInput()
    {
        return this->input;
    }

    b2RayCastOutput& getOutput()
    {
        return this->output;
    }

    b2Fixture& getFixture()
    {
        return *this->rayFixture;
    }

    void setFixture( b2Fixture* fixture )
    {
        this->rayFixture = fixture;
    }

private:
    b2Fixture* rayFixture;

    b2RayCastInput input;
    b2RayCastOutput output;
};

#endif /* RayCastComponent_h */
