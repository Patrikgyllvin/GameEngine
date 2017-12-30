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
    height( 1.0 )
    {
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set( 0.0, 0.0 );
        bodyDef.linearVelocity.Set( 0.0, 0.0 );
        bodyDef.angle = 0.0;
        
        static_cast< b2PolygonShape* >( shape )->SetAsBox( 1.0, 1.0 );
        
        fixtureDef.shape = shape;
        fixtureDef.density = density;
        fixtureDef.restitution = 0.2;
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
    height( height )
    {
        bodyDef.type = type;
        bodyDef.position = position;
        bodyDef.linearVelocity = linVel;
        bodyDef.angle = angle;
        
        static_cast< b2PolygonShape* >( shape )->SetAsBox( width, height );
        
        fixtureDef.shape = shape;
        fixtureDef.density = density;
        fixtureDef.filter.categoryBits = category;
        fixtureDef.filter.maskBits = collideMask;
        fixtureDef.restitution = 0.2;
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
    height( height )
    {
        static_cast< b2PolygonShape* >( shape )->SetAsBox( width, height );
        
        fixtureDef.shape = shape;
        fixtureDef.density = density;
        fixtureDef.filter.categoryBits = category;
        fixtureDef.filter.maskBits = collideMask;
        fixtureDef.restitution = 0.2;
    }
    
    // Doesn't work right with the radius. Don't use.
    PhysicsBodyComponent( b2BodyDef bodyDef, b2FixtureDef fixDef, b2Shape* shape, float32 width, float32 height, float32 density )
    :
    Component( COMPONENT_PHYSICS ),
    body( nullptr ),
    bodyDef( bodyDef ),
    fixtureDef( fixDef ),
    shape( shape ),
    density( density ),
    width( width ),
    height( height )
    {
        fixtureDef.shape = shape;
    }
    
    ~PhysicsBodyComponent()
    {
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
    
private:
    b2Body* body;
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2Shape* shape;
    
    float32 density;
    float32 width, height;
};

#endif /* PhysicsBodyComponent_h */
