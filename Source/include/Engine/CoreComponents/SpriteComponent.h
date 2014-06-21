#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"

namespace Engine
{
	class SpriteComponent : public Component
	{
	public:
		SpriteComponent() : Component( COMPONENT_SPRITE ) {}
		virtual ~SpriteComponent() {}

		bool getPerspective()
		{
			return perspective;
		}



	private:
		bool perspective;
		int spriteW, spriteH, texIndexX, texIndexY;
	};
}

#endif
