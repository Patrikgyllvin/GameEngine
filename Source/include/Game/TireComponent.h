//
//  TireComponent.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-20.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#ifndef TireComponent_h
#define TireComponent_h

#include "../Engine/CoreComponents/Component.h"

class TireComponent : public Engine::Component
{
public:
    TireComponent()
    :
    Component( COMPONENT_TIRE )
    {}
    
    ~TireComponent()
    {}
    
private:
    
};

#endif /* TireComponent_h */
