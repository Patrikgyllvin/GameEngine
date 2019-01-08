#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "System.h"

#include "../CoreComponents/SpriteComponent.h"
#include "../CoreComponents/AnimationComponent.h"

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
