//
//  CameraComponent.h
//  GameEngine
//
//  Created by Patrik Gyllvin on 2017-09-13.
//  Copyright © 2017 Patrik Gyllvin. All rights reserved.
//

#ifndef CameraComponent_h
#define CameraComponent_h

#include "../Engine/CoreComponents/Component.h"

class CameraComponent : public Engine::Component
{
public:
    CameraComponent()
    :
    Component( COMPONENT_CAMERA )
    {}

    ~CameraComponent()
    {}
};

#endif /* CameraComponent_h */
