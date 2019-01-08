//
//  Track.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2018-01-31.
//  Copyright © 2018 Patrik Gyllvin. All rights reserved.
//

#ifndef Track_h
#define Track_h

#include "PhysicsBodyComponent.h"

#include "Texture.h"

#include "../Engine/EntityCore/Entity.h"

class Track
{
public:
    Track( const Texture& texture, Engine::EntityManager& entityManager );
    virtual ~Track();

    Track& makeCurrent();
    void remove();

private:
    const Texture& map;
    std::vector< Engine::Entity* > blocks;

    bool isCurrent;

    Engine::EntityManager& entityManager;
};

#endif /* Track_h */
