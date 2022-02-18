#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "System.h"

#include "Engine/CoreComponents/SpriteComponent.h"
#include "Engine/CoreComponents/AnimationComponent.h"

namespace Engine
{
  class AnimationSystem : public System
  {
  public:
	  AnimationSystem();
	  virtual ~AnimationSystem();

  protected:
	  virtual void init( EntityManager& entityManager );

	  virtual void preProcess();
	  virtual void processEntity( Entity& entity );
	  virtual void postProcess();
  };
}

#endif
