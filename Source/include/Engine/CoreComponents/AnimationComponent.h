#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <iostream>

#include <string>
#include <vector>

#include <GLFW/glfw3.h>

#include "Component.h"
#include "Animation.h"

namespace Engine
{
    class AnimationComponent : public Component
    {
    public:
        AnimationComponent()
        :
        active( nullptr ),
        Component( COMPONENT_ANIMATION )
        {}

        void addAnimation( Animation* animation )
        {
            bool exists = false;

            for( std::vector< Animation* >::iterator it = animations.begin(); it != animations.end(); ++it )
            {
                if( (*it)->getName() == animation->getName() )
                    exists = true;
            }

            if( !exists )
                animations.push_back( animation );
            else
                std::cout << "Animation already exists!\n";
        }

        void removeAnimation( std::string animation )
        {
            for( std::vector< Animation* >::iterator it = animations.begin(); it != animations.end(); ++it )
            {
                if( (*it)->getName() == animation )
                {
                    delete * it;
                    it = animations.erase( it );
                }
            }
        }

        void setActiveAnimation( std::string animation )
        {
            for( std::vector< Animation* >::iterator it = animations.begin(); it != animations.end(); ++it )
            {
                if( active != nullptr )
                    active->setInactive();

                active = *it;
            }
        }

        int getFrame()
        {
            if( active != nullptr )
                active->getFrame();
        }

    private:
       Animation* active;

       std::vector< Animation* > animations;
    };
}

#endif
