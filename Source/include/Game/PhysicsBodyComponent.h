//
//  PhysicsBodyComponent.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-07.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#ifndef PhysicsBodyComponent_h
#define PhysicsBodyComponent_h

#include <Box2D/Box2D.h>

#include "../Engine/CoreComponents/Component.h"

class PhysicsBodyComponent : public Engine::Component
{
public:
    PhysicsBodyComponent()
    :
    Component( COMPONENT_PHYSICS ),
    body( nullptr ),
    bodyDef(),
    fixtureDef(),
    shape( new b2PolygonShape ),
    density( 1.0 ),
    width( 1.0 ),
    height( 1.0 ),
    alive( true )
    {
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set( 0.0, 0.0 );
        bodyDef.linearVelocity.Set( 0.0, 0.0 );
        bodyDef.angle = 0.0;
        bodyDef.userData = this;

        static_cast< b2PolygonShape* >( shape )->SetAsBox( 1.0, 1.0, b2Vec2( 0, 0 ), 0.0 );

        fixtureDef.shape = shape;
        fixtureDef.density = density;
        fixtureDef.friction = 0.8;
        fixtureDef.restitution = 0.2;
        fixtureDef.userData = new b2Vec3( 1.0, 1.0, 0.0 );
    }

    PhysicsBodyComponent( b2BodyType type, b2Vec2 position, b2Vec2 linVel, float32 angle, float32 width, float32 height, uint16 category, uint16 collideMask, float32 density )
    :
    Component( COMPONENT_PHYSICS ),
    body( nullptr ),
    bodyDef(),
    fixtureDef(),
    shape( new b2PolygonShape ),
    density( density ),
    width( width ),
    height( height ),
    alive( true )
    {
        bodyDef.type = type;
        bodyDef.position = position;
        bodyDef.linearVelocity = linVel;
        bodyDef.angle = angle;
        bodyDef.userData = this;

        static_cast< b2PolygonShape* >( shape )->SetAsBox( width, height, b2Vec2( 0, 0 ), 0.0 );

        fixtureDef.shape = shape;
        fixtureDef.density = density;
        fixtureDef.friction = 0.8;
        fixtureDef.filter.categoryBits = category;
        fixtureDef.filter.maskBits = collideMask;
        fixtureDef.restitution = 0.2;
        fixtureDef.userData = new b2Vec3( width, height, 0.0 );
    }

    PhysicsBodyComponent( b2BodyDef bodyDef, float32 width, float32 height, uint16 category, uint16 collideMask, float32 density )
    :
    Component( COMPONENT_PHYSICS ),
    body( nullptr ),
    bodyDef( bodyDef ),
    fixtureDef(),
    shape( new b2PolygonShape ),
    density( density ),
    width( width ),
    height( height ),
    alive( true )
    {
        this->bodyDef.userData = this;

        static_cast< b2PolygonShape* >( shape )->SetAsBox( width, height, b2Vec2( 0, 0 ), 0.0 );

        fixtureDef.shape = shape;
        fixtureDef.density = density;
        fixtureDef.friction = 0.8;
        fixtureDef.filter.categoryBits = category;
        fixtureDef.filter.maskBits = collideMask;
        fixtureDef.restitution = 0.2;
        fixtureDef.userData = new b2Vec3( width, height, 0.0 );
    }

    PhysicsBodyComponent( b2BodyDef bodyDef, b2FixtureDef fixDef, b2Shape* shape, float32 width, float32 height, float32 density )
    :
    Component( COMPONENT_PHYSICS ),
    body( nullptr ),
    bodyDef( bodyDef ),
    fixtureDef( fixDef ),
    shape( shape ),
    density( density ),
    width( width ),
    height( height ),
    alive( true )
    {
        this->bodyDef.userData = this;

        fixtureDef.shape = shape;
        fixtureDef.density = density;
        fixtureDef.userData = new b2Vec3( width, height, 0.0 );
    }

    ~PhysicsBodyComponent()
    {
        for( b2Fixture* f = this->body->GetFixtureList(); f; f = f->GetNext() )
        {
            if( f->GetUserData() )
            {
                delete static_cast< b2Vec3* >( f->GetUserData() );
            }
        }

        this->body->GetWorld()->DestroyBody( body );

        delete shape;
    }

    PhysicsBodyComponent& setBody( b2Body* body )
    {
        if( this->body == nullptr )
            this->body = body;

        return *this;
    }

    b2Body* getBody()
    {
        return this->body;
    }

    const b2BodyDef& getBodyDefinition()
    {
        return this->bodyDef;
    }

    const b2FixtureDef& getFixtureDefinition()
    {
        return this->fixtureDef;
    }

    const b2Shape& getShape()
    {
        return *this->shape;
    }

    float32 getDensity()
    {
        return this->density;
    }

    float32 getHalfWidth()
    {
        return this->width;
    }

    float32 getHalfHeight()
    {
        return this->height;
    }

    float32 getWidth()
    {
        return this->width * 2;
    }

    float32 getHeight()
    {
        return this->height * 2;
    }

    const bool& isAlive() const
    {
        return this->alive;
    }

    void setAlive( const bool& alive )
    {
        this->alive = alive;
    }

private:
    b2Body* body;
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2Shape* shape;

    float32 density;
    float32 width, height;

    bool alive;
};

#endif /* PhysicsBodyComponent_h */
