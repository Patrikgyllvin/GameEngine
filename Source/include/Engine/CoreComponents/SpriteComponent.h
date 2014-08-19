#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "Component.h"

namespace Engine
{
	class SpriteComponent : public Component
	{
	public:
		SpriteComponent( bool perspective, int width, int height, int texIndexX, int texIndexY )
		:
		isPerspective( perspective ),
		spriteW( width ),
		spriteH( height ),
		texIndexX( texIndexX ),
		texIndexY( texIndexY ),
		Component( COMPONENT_SPRITE )
		{}
		
		virtual ~SpriteComponent() {}

		bool getPerspective()
		{
			return isPerspective;
		}

		int getWidth()
		{
			return spriteW;
		}

		int getHeight()
		{
			return spriteH;
		}

		int getTexIndexX()
		{
			return texIndexX;
		}

		int getTexIndexY()
		{
			return texIndexY;
		}
		
		void setTexIndexX( int texX )
		{
			texIndexX = texX;
		}

		void setTexIndexY( int texY )
		{
			texIndexY = texY;
		}
	private:
		bool isPerspective;
		int spriteW, spriteH, texIndexX, texIndexY;
	};
}

#endif
