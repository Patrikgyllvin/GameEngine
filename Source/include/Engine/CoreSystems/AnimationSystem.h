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
	  AnimationSystem( EventManager* evtManager, EntityManager* entityManager );
	  virtual ~AnimationSystem();

  protected:
	  virtual void init();
      
      // TODO: NAMES
/*
	  virtual void preUpdate();
	  virtual void updateEntities( const Entity& entities );
	  virtual void postUpdate();
*/
  private:
	  void updateEntityAnimation( Entity* entity );
  };
}

#endif