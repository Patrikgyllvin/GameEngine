#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Component.h"
#include "../../ComponentTypes.h"

namespace Engine
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent()
        :
        Component( COMPONENT_TRANSFORM ),
        posX( 0 ),
        posY( 0 ),
        posZ( 0 ),
        rotX( 0 ),
        rotY( 0 ),
        rotZ( 0 ),
        scaleX( 0 ),
        scaleY( 0 ),
        scaleZ( 0 )
        {}
        
		virtual ~TransformComponent()
        {}

		TransformComponent& setPosition( float x, float y, float z )
		{
			posX = x;
			posY = y;
			posZ = z;

			return *this;
		}

		TransformComponent& setPosX( float x )
		{
			posX = x;

			return *this;
		}

		TransformComponent& setPosY( float y )
		{
			posY = y;

			return *this;
		}

		TransformComponent& setPosZ( float z )
		{
			posZ = z;

			return *this;
		}


		float getPosX()
		{
			return this->posX;
		}

		float getPosY()
		{
			return this->posY;
		}

		float getPosZ()
		{
			return this->posZ;
		}


		// TODO: Change to quaternion...
		TransformComponent& setRotation( float x, float y, float z )
		{
			rotX = x;
			rotY = y;
			rotZ = z;

			return *this;
		}

		TransformComponent& setRotX( float x )
		{
			rotX = x;

			return *this;
		}

		TransformComponent& setRotY( float y )
		{
			rotY = y;

			return *this;
		}

		TransformComponent& setRotZ( float z )
		{
			rotZ = z;

			return *this;
		}

		float getRotX()
		{
			return this->rotX;
		}

		float getRotY()
		{
			return this->rotY;
		}

		float getRotZ()
		{
			return this->rotZ;
		}


		TransformComponent& setScale( float x, float y, float z )
		{
			scaleX = x;
			scaleY = y;
			scaleZ = z;

			return *this;
		}

		TransformComponent& setScaleX( float x )
		{
			scaleX = x;

			return *this;
		}

		TransformComponent& setScaleY( float y )
		{
			scaleY = y;

			return *this;
		}

		TransformComponent& setScaleZ( float z )
		{
			scaleZ = z;

			return *this;
		}

		float getScaleX()
		{
			return this->scaleX;
		}

		float getScaleY()
		{
			return this->scaleY;
		}

		float getScaleZ()
		{
			return this->scaleZ;
		}

	private:
		float posX, posY, posZ;

		// TODO: Change to quaternion...
		float rotX, rotY, rotZ;

		float scaleX, scaleY, scaleZ;
	};
}

#endif
