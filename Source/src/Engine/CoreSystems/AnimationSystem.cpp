#if !defined(__APPLE__) || defined(_MAC_MAKEFILE)
#include "Engine/CoreSystems/AnimationSystem.h"
#else
#include "AnimationSystem.h"
#endif

namespace Engine
{
	AnimationSystem::AnimationSystem( EventManager* evtManager, EntityManager* entityManager )
	//System( evtManager, entityManager, COMPONENT_ANIMATION_BIT | COMPONENT_ANIMATION_BIT )
	{}

	AnimationSystem::~AnimationSystem()
	{}

	void AnimationSystem::init()
	{}
/*
	void AnimationSystem::preUpdate()
	{}
*//*
	void AnimationSystem::updateEntities( const std::set< Entity* >& entities )
	{
		for( std::set< Entity* >::const_iterator it = entities.begin(); it != entities.end(); ++it )
		{
			updateEntityAnimation( *it );
		}
	}

	void AnimationSystem::updateEntityAnimation( Entity* entity )
	{
		SpriteComponent* spriteComp = static_cast< SpriteComponent* >( entityManager->getComponent( entity, COMPONENT_SPRITE ) );
		AnimationComponent* animComp = static_cast< AnimationComponent* >( entityManager->getComponent( entity, COMPONENT_ANIMATION ) );

		int currFrame = animComp->getFrame();

		int texWidth = 256;
		int texHeight = 256;

		int rows = texWidth / spriteComp->getWidth();;
		int columns = texHeight / spriteComp->getHeight();;

		spriteComp->setTexIndexX( currFrame % rows );
		spriteComp->setTexIndexY( currFrame / columns );
	}
*/
}