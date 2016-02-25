#if !defined(__APPLE__) || defined(_MAC_MAKEFILE)
#include "../../../include/Engine/CoreSystems/AnimationSystem.h"
#else
#include "AnimationSystem.h"
#endif

namespace Engine
{
	AnimationSystem::AnimationSystem( EventManager* evtManager, EntityManager* entityManager )
	{}

	AnimationSystem::~AnimationSystem()
	{}

	void AnimationSystem::init()
	{}

	void AnimationSystem::preProcess()
	{}

	void AnimationSystem::processEntity( Entity& entity )
	{
		std::vector< Component* >& spriteComps = entity.getComponents( COMPONENT_SPRITE );
		std::vector< Component* >& animComps = entity.getComponents( COMPONENT_ANIMATION );
		
		// TODO: Remove quickfix :D Though makes no sense to use multiple spritecomponents etc.
		SpriteComponent* spriteComp = static_cast< SpriteComponent* >( spriteComps[ 0 ] );
		AnimationComponent* animComp = static_cast< AnimationComponent* >( animComps[ 0 ] );

		int currFrame = animComp->getFrame();

		int texWidth = 256;
		int texHeight = 256;

		int rows = texWidth / spriteComp->getWidth();
		int columns = texHeight / spriteComp->getHeight();

		spriteComp->setTexIndexX( currFrame % rows );
		spriteComp->setTexIndexY( currFrame / columns );
	}

	void AnimationSystem::postProcess()
	{}
}