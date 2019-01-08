//
//  Track.cpp
//  GameEngine
//
//  Created by Patrik Gyllvin on 2018-01-31.
//  Copyright © 2018 Patrik Gyllvin. All rights reserved.
//

#include "../../include/Game/Track.h"

Track::Track( const Texture& texture, Engine::EntityManager& entityManager )
:
map( texture ),
isCurrent( false ),
entityManager( entityManager )
{}

Track::~Track()
{}

Track& Track::makeCurrent()
{
    if( isCurrent )
        return *this;

    const png::image< png::rgba_pixel >& image = map.getRawImage();

    Engine::Entity* entity;
    for( int x = 0; x != map.getWidth(); ++x )
    {
        for( int y = 0; y != map.getHeight(); ++y )
        {
            png::rgba_pixel pixel = image.get_pixel( x, y );

            if( (int)pixel.red == 255 && (int)pixel.green == 255 && (int)pixel.blue == 255 && (int)pixel.alpha == 255 )
            {
                b2BodyDef bDef;
                bDef.type = b2_staticBody;
                bDef.position = b2Vec2( x - map.getWidth() / 2.0, -y + map.getHeight() / 2.0 );
                bDef.linearVelocity = b2Vec2( 0, 0 );
                bDef.angle = 0.0;

                entity = &entityManager.genEntity().addComponent( new PhysicsBodyComponent( bDef, 0.5, 0.5, 0x0002, 0x0001, 1 ) );

                blocks.push_back( entity );
            }
        }
    }

    return *this;
}

void Track::remove()
{
    if( !isCurrent )
        return;

    for( auto it = blocks.begin(); it != blocks.end(); ++it )
    {
        (*it)->destroyEntity();
    }
}
