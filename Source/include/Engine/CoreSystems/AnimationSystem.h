#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "System.h"

#include "../CoreComponents/SpriteComponent.h"
#include "../CoreComponents/AnimationComponent.h"

class AnimationSystem : public System
{
public:
	AnimationSystem( EventManager* evtManager, EntityManager* entityManager );
	virtual ~AnimationSystem();

protected:
	virtual void init();

	virtual void preUpdate();
	virtual void updateEntities( const std::set< Entity* >& entities );
	virtual void postUpdate();

private:
	void updateEntityAnimation( Entity* entity );
};

#endif